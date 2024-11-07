#pragma 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>//time.h也行
#include <cstdarg>
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
using std::string;
namespace hobert
{
	namespace utility
	{
		#define log_debug(format,...)\
			Logger::instance()->log(Logger::LOG_DEBUG,__FILE__,__LINE__,format,##__VA_ARGS__)
		#define log_info(format,...)\
			Logger::instance()->log(Logger::LOG_INFO,__FILE__,__LINE__,format,##__VA_ARGS__)
		#define log_warn(format,...)\
			Logger::instance()->log(Logger::LOG_WARN,__FILE__,__LINE__,format,##__VA_ARGS__)
		#define log_error(format,...)\
			Logger::instance()->log(Logger::LOG_ERROR,__FILE__,__LINE__,format,##__VA_ARGS__)
		#define log_fatal(format,...)\
			Logger::instance()->log(Logger::LOG_FATAL,__FILE__,__LINE__,format,##__VA_ARGS__)
		class Logger
		{
		public:
			enum Level
			{
				LOG_DEBUG =0,
				LOG_INFO,
				LOG_WARN,
				LOG_ERROR,
				LOG_FATAL,
				LOG_COUNT
			};
			

			static Logger* instance();//静态方法获取指针
			void open(const string& filename);
			void close();
			void log(Level level, const char* file, int line, const char* format, ...);

			void set_level(int level);//设置日志级别
			void set_max_size(int size);
			void set_console(bool console);
		private:
			Logger();//单例模式下将构造、析构函数申明为私有 不允许 Logger log;的实例化对象
			~Logger();
			void rotate();//日志翻滚
			void sleep(int milliseconds);
			void localtime(struct tm* time_info, const time_t* ticks);


		private:
			string m_filename;
			std::ofstream m_ofs;
			int m_max;//日志文件大小
			int m_len;//
			int m_level;
			bool m_console;//是否在控制台打印
			static const char* s_level[LOG_COUNT];//创建存储level个数的数组

			static Logger* m_instance;//单例 静态成员指针
		};
	}
}