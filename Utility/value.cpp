#include "value.h"

using namespace hobert::utility;

Value::Value() : m_type(V_NULL)
{

}

Value::Value(bool value) :m_type(V_BOOL)
{
	m_value = value ? "ture" : "false";
};
Value::Value(int value) :m_type(V_INT)
{
	m_value = std::to_string(value);
};
Value::Value(unsigned int value) :m_type(V_INT)
{
	m_value = std::to_string(value);
};
Value::Value(float value) :m_type(V_FLOAT)
{
	m_value = std::to_string(value);
};
Value::Value(double value) :m_type(V_DOUBLE)
{
	m_value = std::to_string(value);
};
Value::Value(const char* value) :m_type(V_STRING)
{
	m_value = value;
};//c语言字符串
Value::Value(const string& value) :m_type(V_STRING)
{
	m_value = value;
};//c++ string;
Value& Value::operator = (bool value)
{
	m_type = V_BOOL;
	m_value = value ? "ture" : "false";
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (int value)
{
	m_type = V_INT;
	m_value = std::to_string(value);
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (unsigned int value)
{
	m_type = V_INT;
	m_value = std::to_string(value);
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (float value)
{
	m_type = V_FLOAT;
	m_value = std::to_string(value);
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (double value)
{
	m_type = V_DOUBLE;
	m_value = std::to_string(value);
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (const char* value)
{
	m_type = V_STRING;
	m_value = value;
	return *this; //返回这个指针的解引用
};
Value& Value::operator = (const string& value)
{
	m_type = V_STRING;
	m_value = value;
	return *this; //返回这个指针的解引用
}
Value& Value::operator=(const Value& other)
{
	m_type = other.m_type;
	m_value = other.m_value;
	return *this; //返回这个指针的解引用
}
;
Value::Type Value::type() const
{
	return m_type;
};
bool Value::is_null() const
{
	return m_type == V_NULL;
};
bool Value::is_bool() const
{
	return m_type == V_BOOL;

};
bool Value::is_int() const
{
	return m_type == V_INT;
};
bool Value::is_float() const
{
	return m_type == V_FLOAT;
};
bool Value::is_double() const
{
	return m_type == V_DOUBLE;
};
bool Value::is_string() const
{
	return m_type == V_STRING;
};
bool Value::operator == (const Value& other)
{
	if (m_type != other.m_type)
	{
		return false;
	}
	return m_value == other.m_value;
};
bool Value::operator != (const Value& other)
{
	return !(*this == other);
};
Value::operator bool()
{
	return m_value == "ture" ? true : false;
};
Value::operator int()
{
	int value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;

};
Value::operator unsigned int()
{
	unsigned int value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;
};
Value::operator float()
{
	float value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;
};
Value::operator double()
{
	double value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;

};
Value::operator string()
{
	return m_value;
};
Value::operator bool() const
{
	return m_value == "ture" ? true : false;
};
Value::operator int() const
{
	int value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;

};
Value::operator unsigned int() const
{
	unsigned int value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;
};
Value::operator float() const
{
	float value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;
};
Value::operator double() const
{
	double value = 0;
	std::stringstream ss;
	ss << m_value;
	ss >> value;
	return value;

};
Value::operator string() const
{
	return m_value;
};
void Value::show() const
{
	string type;
	switch (m_type)
	{
		case V_NULL:
			type = "null";
			break;
		case V_BOOL:
			type = "bool";
			break;
		case V_INT:
			type = "int";
			break;
		case V_FLOAT:
			type = "float";
			break;
		case V_DOUBLE:
			type = "double";
			break;
		case V_STRING:
			type = "string";
			break;
		default:
			break;

	}
	std::cout << "type=" << type << ", value=" << m_value << std::endl;
}
