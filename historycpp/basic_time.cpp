// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include "Utility/time.h"
using namespace hobert::utility;
int main(int argc, char* argv[])
{
	Time t;

	t.show();

	std::cout << "sec:" << t.seconds() << ", milliseconds:" << t.milliseconds() << std::endl;
	std::cout << t.format("%Y-%m-%d %H:%M:%S") << std::endl;
	return 0;
}
