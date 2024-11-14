// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include "Utility/String.h"
using namespace hobert::utility;

int main(int argc, char* argv[])
{
	//std::cout << String::ltrim("ABCAB", "AB") << std::endl;
	//std::cout << String::rtrim("hello world", "dl") << std::endl;
	//std::cout << String::rtrim("hello world", "dlr") << std::endl;
	//std::cout << String::rtrim("hello world", "dlo") << std::endl;
	//std::cout << String::trim("hello world", "dloh") << std::endl;

	//const string input = "";
	//std::vector<string> output = String::split(input, '/');
	//for (auto& s : output)
	//{
	//	std::cout << s << std::endl;
	//}
	//std::cout << "1" << std::endl;

	//std::vector<string> input;
	//input.push_back("aa");
	//input.push_back("bb");
	//std::cout<<String::join(input,'/')<<std::endl;

	//std::cout << String::capitalize("hello") << std::endl;

	std::cout << String::format("name=%s age=%d", "jack", 18) << std::endl;
	return 0;
}
