#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <string>

using std::string;
namespace hobert
{
	namespace utility
	{
		class Option
		{
		public:
			enum Type //types of command line parameter
			{
				OPT_UNKNOWN = 0,
				OPT_NO,
				OPT_REQUIRED,
				OPT_OPTIONAL
			};

			Option() = default;
			~Option() = default;
			void add(const string & opt, Type type);
			Type type(const string & opt) const;//1st 'const' for protect parameter from being edited;
												//2nd 'const' means only read,no operation to member's value
												//'&' for no creating a copy of 'opt', but refer to itself
			void parse(int argc, char* argv[]);//解析，argc:命令行参数个数(参数间用空格隔开) argv:指向字符串数组的指针
			void show()const;
			bool has(const string& opt)const;//是否有参数
			bool get_bool(const string& opt);
			int get_int(const string& opt);
			string get_string(const string& opt);
		private:
			std::map<string, Type> m_opts;//name,type
			std::map<string, string> m_args;//name,value
		};

	}
}