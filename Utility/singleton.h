#pragma once
namespace hobert
{
	namespace utility
	{
		template<typename T>//指定下面是模板类 <typename T>是模板参数
		class Singleton
		{
		public:
			static T* instance()
			{
				static T instance;//C++1保证局部静态线程安全
				return &instance;
			}
		private:
			Singleton()=default;
			Singleton(const Singleton<T>& other) = delete;//拷贝构造
			Singleton<T>& operator = (const Singleton<T>&) = delete;//赋值构造函数
			~Singleton() = default;
		};


#define SINGLETON(classname)							\
friend class Singleton<classname>;						\
private:												\
	classname() = default;								\
	classname(const classname &) = delete;				\
	classname & operator = (const classname &)=delete;	\
	~classname() = default

	}
}