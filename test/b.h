#pragma once
#include <iostream>
#include "../Utility/singleton.h"
using namespace hobert::utility;
class B
{
	SINGLETON(B);
public:

	void show()
	{
		std::cout << "B" << std::endl;
	}

};
