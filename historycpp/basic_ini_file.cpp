// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include "Utility/ini_file.h"

using namespace hobert::utility;

int main(int argc, char* argv[])
{
	IniFile ini("../../../main.ini");
	//const string& ip = ini.get("server", "ip");
	const string& ip = ini["server"]["ip"];
	std::cout << ip << std::endl;
	ini["server"]["ip"] = "192.168.1.1";
	ini.set("server", "port", 8080);

	ini.show();
	ini.save("../../../main1.ini");
	return 0;
}
