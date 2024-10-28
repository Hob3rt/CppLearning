#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

using std::string;
#include "value.h"

namespace hobert
{
	namespace utility
	{
		class IniFile
		{
			typedef std::map<string, Value> Section;
		public:
			IniFile() = default;
			IniFile(const string& filename);
			~IniFile() = default;

			bool load(const string& filename);
			string str()const;//返回ini文件内容
			void show();

			Value& get(const string& section, const string& key);	//&意义：它以引用方式返回函数值,省去拷贝开销
																	//1.省去拷贝开销
																	//2.允许修改原对象：通过返回引用，调用者可以直接修改被引用的对象
																	// string& ip = ini.get("server", "ip"); 可以通过ip修改ini中的server ip
																	// const string& ip = ini.get("server", "ip");不可以通过ip修改ini中的server ip
																	// string ip = ini.get("server", "ip"); ip 仍然是ini中server ip的拷贝，不能修改ini中的值
																	//注意：1.不要将局部变量（例如次函数内定义的非static变量）作为返回值
																	//2.函数返回值可以作为左值												
			void set(const string& section, const string& key, const Value& value);
			Section& operator[] (const string& section)
			{
				return m_sections[section];
			}

			bool has(const string& section);//是否有某字段
			bool had(const string& section, const string& key);//

			void remove(const string& section);
			void remove(const string& section, const string& key);
			void clear();
			void save(const string &filename);
		private:
			string trim(string s);//去换行符

		private:
			string m_filename;
			std::map<string, Section> m_sections;
		};
	}
}