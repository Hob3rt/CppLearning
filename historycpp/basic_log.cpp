// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include "Utility/logger.h"

using namespace hobert::utility;

int main(int argc, char* argv[])
{
	Logger;
	Logger::instance()->open("../../../main.log");
	Logger::instance()->set_max_size(1024);
	Logger::instance()->set_console(true);
	for (int i = 0; i < 100; i++)
	{
		//Logger::instance()->log(Logger::LOG_DEBUG, __FILE__, __LINE__, "%s %d", "hello world", 123);
		log_debug("%s %d", "hello world", 123);
		log_error("%s", "it's an error");
	}

	return 0;
}
