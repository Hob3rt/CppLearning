#include "option.h"
#include <stdexcept>
using namespace hobert::utility;
void Option::add(const string& opt, Type type)
{
	m_opts[opt] = type;
}

Option::Type Option::type(const string & opt) const
{
	auto it = m_opts.find(opt);
	if (it == m_opts.end())
	{
		return OPT_UNKNOWN;
	}
	return it->second;
}

void Option::parse(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++) //index start from '1',for excluding the 1st(index 0) char which is the name&path of executable file
	{
		string arg = argv[i];
		if (arg.substr(0, 1) != "-") //判断是否为选项参数
		{
			//忽略普通参数
			continue;
		}
		if (arg.substr(0, 2) == "--")
		{
			//长参数解析 以“--”开头的
			string str = arg.substr(2);
			auto pos = str.find('=');
			if (pos != std::string::npos)//如果有"="
			{
				//有"=",表示参数可能是必选参数或可选参数
				string opt = str.substr(0, pos);
				string val = str.substr(pos + 1);
				switch (type(opt))
				{
					case OPT_NO:
					{
						throw std::logic_error("no argument option:" + opt);
					}
					case OPT_OPTIONAL:
					case OPT_REQUIRED://different cases share a same {}
					{
						m_args[opt] = val;
						break;
					}
					default:
						break;
				}
			}
			else
			{
				//处理不带“=”的
				switch (type(str))
				{
					case OPT_NO:
					case OPT_OPTIONAL:
					{
						m_args[str] = "";
						break;
					}
					case OPT_REQUIRED:
					{
						//不带=的，需要值的参数，名与值空格隔开，值在下一个字符串上(--name Jack)
						if (i + 1 > argc)
						{
							//超出数组，但参数没值
							throw std::logic_error("option required argument:" + str);
						}
						string val = argv[i + 1];
						if (val.substr(0, 1) == "-")
						{
							//参数漏掉值，直接到下个参数
							throw std::logic_error("option missing argument:" + str);
						}
						m_args[str] = val;
						i++;//跳过下一个
						break;
					}
					default:
						break;
				}
		}
			}
		else
		{
			//短参数解析，以“-"开头: -a -b "-"加一个字母。或者-a -b -c合并为-abc 的情况
			string opt = arg.substr(1, 1);
			switch (type(opt))
			{
				case OPT_NO:
				{
					if (arg.length() >= 2)
					{
						//处理合并参数
						for (int k = 1;k<arg.length();k++)
						{
							string o(1, arg[k]);//创建以1个arg[k]字母的字符串o
							if (type(o) != OPT_NO)
							{
								continue;
							}
							m_args[o] = "";
						}
					}
					break;
				}
				case OPT_OPTIONAL:
				{
					if (arg.length() > 2)
					{
						m_args[opt] = arg.substr(2);
					}
					else
					{
						m_args[opt] = "";
					}
					break;
				}
				case OPT_REQUIRED:
				{
					if (i + 1 >= argc)
					{
						throw std::logic_error("option required argument:" + opt);
					}
					string val = argv[i + 1];
					if (val.substr(0, 1) == "-")
					{
						throw std::logic_error("option messing argument:" + opt);
					}
					m_args[opt] = val;
					i++;
					break;
				}
				default:
					break;
			}
		}
	}
}

void Option::show() const
{
	for (const auto& pair : m_args)
	{
		std::cout << pair.first << ":" << pair.second << std::endl;
	}
}

bool Option::has(const string& opt) const
{
	auto it = m_opts.find((opt));
	if (it == m_opts.end())
	{
		return false;
	}
	return m_args.find(opt) != m_args.end();
}

bool Option::get_bool(const string& opt)
{
	return m_args.find(opt) != m_args.end();
};
int Option::get_int(const string& opt)
{
	auto it=m_args.find(opt);
	if (it == m_args.end())
	{
		return 0;
	}
	int value = 0;
	std::stringstream ss;
	ss << it->second;
	ss >> value;
	return value;
};
string Option::get_string(const string& opt)
{
	auto it = m_args.find(opt);
	if (it == m_args.end())
	{
		return "";
	}
	return it->second;
};
