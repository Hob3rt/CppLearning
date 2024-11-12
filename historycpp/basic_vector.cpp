// CppLearning.cpp : Defines the entry point for the application.

#include <iostream>
#include <vector>
#include "stl/vector.h"
using namespace hobert::stl;
int main(int argc, char* argv[])
{
	Vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.show();
	v.insert(v.begin(), 2, 33);
	v.erase(v.begin() + 2);
	v.show();
	return 0;
}
