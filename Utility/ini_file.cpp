#include "ini_file.h"
using namespace hobert::utility;
IniFile::IniFile(const string& filename)
{
	load(filename);
}

bool IniFile::load(const string& filename)
{
	m_sections.clear();
	m_filename = filename;
	std::ifstream ifs(filename);
	if (ifs.fail())
	{
		throw std::logic_error("loading ini file failed:" + filename);
	}
	string name;
	string line;
	while (std::getline(ifs, line))//getline得到的line包含换行符
	{
		line = trim(line);
		if (line.empty())
		{
			continue;
		}
		if (line[0] == '#' || line[0] == ';')//判断是否是注释
		{
			continue;
		}
		if (line[0] == '[')//一个section开始
		{
			auto pos = line.find_first_of(']');
			if(pos==std::string::npos)
			{
				throw std::logic_error("invalid section: " + line);
			}
			name = trim(line.substr(1, pos - 1));//去掉[]得到name
			m_sections[name] = Section();
		}
		else//处理key = value
		{
			auto pos = line.find_first_of('=');
			if (pos == std::string::npos)
			{
				throw std::logic_error("invalid option: " + line);
			}
			string key = line.substr(0, pos);
			key = trim(key);

			string value = line.substr(pos+1);
			value = trim(value);
			m_sections[name][key] = value;
		}
	} 
	return true;
	
}

string hobert::utility::IniFile::str() const
{
	std::stringstream ss;
	for (const auto& section : m_sections)
	{
		ss << "[" << section.first << "]" << std::endl;
		for (const auto& option : section.second)
		{
			ss << option.first << " = " << (string)(option.second) << std::endl;
		}
		ss << std::endl;
	}
	return ss.str();
}

void hobert::utility::IniFile::show()
{
	std::cout << str();
}

Value& hobert::utility::IniFile::get(const string& section, const string& key)
{
	if (m_sections[section][key].is_null())
	{
		std::cout << "Value of \"Section:" << section << " Option:" << key << "\" is not found." << std::endl;
	}
	
	return m_sections[section][key];//如果找不到m_sections[section][key]，则value类型是NULL

}

void hobert::utility::IniFile::set(const string& section, const string& key, const Value& value)
{
	m_sections[section][key] = value;
}

bool hobert::utility::IniFile::has(const string& section)
{
	
	return m_sections.find(section) != m_sections.end();
}

bool hobert::utility::IniFile::had(const string& section, const string& key)
{
	auto it = m_sections.find(section);
	if(it == m_sections.end())
	{
		return false;
	}
	return it->second.find(key)!=it->second.end();
}

void hobert::utility::IniFile::remove(const string& section)
{
	m_sections.erase(section);
}

void hobert::utility::IniFile::remove(const string& section, const string& key)
{
	auto it = m_sections.find(section);
	if (it == m_sections.end())
	{
		return;
	}
	it->second.erase(key);
}

void hobert::utility::IniFile::clear()
{
	m_sections.clear();
}

void hobert::utility::IniFile::save(const string& filename)
{
	std::ofstream ofs(filename);
	if (ofs.fail())
	{
		throw std::logic_error("saving ini file failed: " + filename);
	}
	ofs << str();
	ofs.close();
}

string IniFile::trim(string s)
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(" \r\n"));//去除开头空格回车换行
	s.erase(s.find_last_not_of(" \r\n") + 1);//去除结尾空格回车换行
	return s;
}
