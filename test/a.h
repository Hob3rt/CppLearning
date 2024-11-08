#pragma once
#include <iostream>
#include "../Utility/singleton.h"
using namespace hobert::utility;
class A
{
	//friend class Singleton<A>;
	SINGLETON(A);
public:
	//static A* instance()
	//{
	//	//if (m_instance == nullptr)
	//	//{
	//	//	m_instance = new A();//多线程时有问题，当另一个线程执行到上一行判断时，一个线程的new可能正在创建中，导致该线程也new了
	//	//}

	//	//local static 线程安全
	//	static A a;

	//	return & a;
	//}
	void show()
	{
		std::cout << "A" << std::endl;
	}
//private:
//	A() = default;//等价于 A(){}
//	A(const A& a)= delete;//拷贝构造函数  delete表示不需要拷贝构造函数
//	A& operator = (const A& a);//赋值构造 delete表示不需要赋值构造函数
//	~A()=default;

//private:
//	static A m_instance;
};

//A A::m_instance;