#pragma once
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif // WIN32
#include <iostream>
#include <ctime>
#include <string>
using std::string;
namespace hobert
{
	namespace utility
	{
		class Time
		{
		public:
			Time();
			~Time() = default;

			int year() const;
			int month()const;
			int day() const;
			int hour() const;
			int minute() const;
			int second() const;//秒钟
			int week() const;

			void show();
			double seconds() const;//1900-01-01以来的秒数
			double milliseconds() const;
			double operator - (const Time& other);//单位微秒

			static void sleep(int millisecond);//睡眠多长

			//format = "%Y-%m-%d %H:%M:%S"
			string format(const string& format) const;
		private:
			void get_local_time(struct tm* tm, const time_t *ticks);
			void get_time_of_day(struct timeval* tv);//跨平台 tv 含 秒数和微妙数
		private:
			struct tm m_tm = { 0 };//struct tm 的tm.tm_year从1900开始
			int m_sec;//mktime 函数返回自1970年1月1日00:00:00以来的秒数
			int m_usec;
		};
	}
}