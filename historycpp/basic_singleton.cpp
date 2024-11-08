// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include "test/a.h"
#include "test/b.h"
#include "Utility/singleton.h"
#include "Utility/logger.h"
using namespace hobert::utility;
int main(int argc, char* argv[])
{
	Singleton<A>::instance()->show();
	Singleton<B>::instance()->show();
	auto logger = Singleton<Logger>::instance();
	logger->open("../../../main.log");
	log_debug("hello");
	return 0;
}
