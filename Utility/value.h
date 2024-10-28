#pragma once
#include <iostream>
#include<sstream>
#include <string>
using std::string;
namespace hobert
{
	namespace utility
	{
		class Value
		{
		public:
			enum Type
			{
				V_NULL = 0,//无类型
				V_BOOL,
				V_INT,
				V_FLOAT,
				V_DOUBLE,
				V_STRING
			};
			Value();
			Value(bool value);
			Value(int value);
			Value(unsigned int value);
			Value(float value);
			Value(double value);
			Value(const char* value);//c语言字符串
			Value(const string& value);//c++ string
			~Value() = default;

			//赋值运算符
			Value& operator = (bool value);
			Value& operator = (int value);
			Value& operator = (unsigned int value);
			Value& operator = (float value);
			Value& operator = (double value);
			Value& operator = (const char* value);
			Value& operator = (const string & value);
			Value& operator = (const Value& other);

			Type type() const;
			bool is_null() const;
			bool is_bool() const;
			bool is_int() const;
			bool is_float() const;
			bool is_double() const;
			bool is_string() const;

			bool operator == (const Value& other);
			bool operator != (const Value& other);

			//类型转换运算符
			operator bool();
			operator int();
			operator unsigned int();
			operator float();
			operator double();
			operator string();

			//类型转换运算符const版本 Value类可能会在别的类中调用，当调用函数如“int foo(const Value& value)”使用const修饰作为参数的value时会调用const版本
			operator bool() const;
			operator int() const;
			operator unsigned int() const;
			operator float() const;
			operator double() const;
			operator string() const;

			void show() const;
		private:
			Type m_type;
			string m_value;
		};
	}
}