#include "logger.h"
using namespace hobert::utility;
const char* Logger::s_level[LOG_COUNT] = {
	"DEBUG","INFO","WARN","ERROR","FATAL"
};

//Logger* Logger::m_instance = nullptr;//main函数运行前静态变量初始化 静态变量存储在进程静态数据区

//Logger::Logger():m_level(LOG_DEBUG),m_max(0),m_console(0)
//{
//};
//Logger::~Logger()
//{
//	close();
//}
//Logger* Logger::instance()
//{
//	if (m_instance == nullptr)
//	{
//		m_instance = new Logger();
//	}
//	return m_instance;
// };
void Logger::open(const string& filename)
{
	m_filename = filename;
	m_ofs.open(filename, std::ios::app);//以追加方式打开文件
	if (m_ofs.fail())
	{
		throw std::logic_error("open log file failed:" + filename);
	}
	m_ofs.seekp(0, std::ios::end);//指针移到末尾
	m_len = (int)m_ofs.tellp();//指针位置
}

void hobert::utility::Logger::close()
{
	m_ofs.close();
}

void hobert::utility::Logger::set_level(int level)
{
	m_level = level;
}
void hobert::utility::Logger::set_max_size(int size)
{
	m_max = size;
};
void hobert::utility::Logger::set_console(bool console)
{
	m_console = console;
};

void hobert::utility::Logger::rotate()
{
	close();
	sleep(1000);//确保每次调用这个函数时的秒数不至于相同，使每个文件名区分开
	time_t ticks = time(nullptr);
	struct tm time_info = { 0 };
	localtime_s(&time_info, &ticks);
	char timestamp[32] = { 0 };
	strftime(timestamp, sizeof(timestamp), ".%Y-%m-%d_%H-%M-%S", &time_info);
	string renamedfile = m_filename + timestamp;//备份重命名当前日志
	if (rename(m_filename.c_str(), renamedfile.c_str())!=0)	//成功时：rename() 返回 0。
																					//失败时：rename() 返回非零值（通常为 - 1），并设置 errno 来指示具体的错误类型。
	{
		return;
	}
	open(m_filename);
}
void hobert::utility::Logger::sleep(int milliseconds)
{
#ifdef WIN32
	Sleep(milliseconds);
#else
	usleep(milliseconds * 1000);
#endif // WIN32

};
void hobert::utility::Logger::localtime(tm* time_info, const time_t* ticks)
{
#ifdef WIN32
	localtime_s(time_info, ticks);
#else
	localtime_r(tick, time_info);
#endif
}
;

void hobert::utility::Logger::log(Level level, const char* file, int line, const char* format, ...)
{
	if (m_level > level)//忽略低级别日志信息
	{
		return;
	}
	if (m_ofs.fail())
	{
		return;
	}
	std::ostringstream oss;
	time_t ticks = time(nullptr);//获取当前时间戳
	struct tm time_info = { 0 };
	localtime_s(&time_info, &ticks);//windows下"_s"表示线程安全
	//把时间戳转成年月日时分秒
	char timestamp[32] = { 0 };
	strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &time_info);
	//std::cout << "ticks=" << ticks << ",timestamp="<<timestamp << std::endl;
	int len = 0;//当前内容长度
	const char* fmt = "%s %s %s:%d ";//格式
	len = snprintf(nullptr, 0, fmt, timestamp, s_level[m_level], file, line);	//snprintf格式化字符串并将其存储到一个字符数组nullptr中
																										//返回值：
																										//成功时，返回需要的字符串长度（不包括空字符 \0），即如果没有长度限制，格式化字符串将占用的字符数。
																										//	如果返回值等于或大于 size，说明输出被截断了，需要更大的缓冲区来存储完整的字符串。
																										//	如果 size 为 0，snprintf 仅计算格式化字符串的长度，但不写入字符数组。
	if (len > 0)
	{
		char* buffer = new char[len + 1];
		snprintf(buffer, len + 1, fmt, timestamp, s_level[m_level], file, line);
		buffer[len] = 0;// 这里用整数 0 表示字符串结束符，等同于 buffer[len] = '\0';
						//在 C 中，字符串是以字符数组的形式存储的，使用空字符 '\0' 来标记字符串的结束。尽管 '\0' 是以字符常量的形式写出来的，它的实际数值仍然是 0，因此直接用 0 来代替 '\0' 是完全可行的。
		oss << buffer;
		m_len += len;
		delete[] buffer;//delete[] 与new[]匹配，为删除/创建分配数组的内存，不带[]是删除/创建分配单个对象的内存
	}
	va_list arg_ptr;//可变参数
	va_start(arg_ptr, format);
	len = vsnprintf(nullptr, 0, format, arg_ptr);
	va_end(arg_ptr);
	if (len > 0)
	{
		char* content = new char[len + 1];
		va_start(arg_ptr, format);
		vsnprintf(content, len + 1, format, arg_ptr);
		va_end(arg_ptr);
		content[len] = 0;
		oss << content;
		delete[]content;
	}
	oss << '\n';
	const string& str = oss.str();
	//std::cout << str << std::endl;
	m_ofs << str;
	m_ofs.flush();//调用 flush() 会强制将缓冲区中的数据立即写入文件，即使缓冲区没有满或文件还没有被关闭。它确保所有之前写入的数据都会被刷新到文件中，从而保证文件中的内容是最新的。
	if (m_console)
	{
		std::cout << str ;
	}
	if (m_max > 0 &&m_len>=m_max)
	{
		rotate();
	}
}


