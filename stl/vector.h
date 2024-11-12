#pragma once
#include <iostream>
#include <stdexcept>
namespace hobert
{
	namespace stl
	{
		template <typename T>
		class Vector
		{
		public:
			Vector();
			~Vector();
			void show()const;

			bool is_basic_tpye();
			void push_back(const T& value);
			void pop_back();
			T& at(int index);
			const T& at(int index) const;//为什么要const版本：在const函数中调用at()，需要const版本的at()
			T& front();
			const T& front() const;
			T& back();
			const T& back() const;

			bool empty() const noexcept; //noexcept表示函数不会抛出异常
			void clear() noexcept;
			int size() const noexcept;
			int capacity() const noexcept;
			T* data() noexcept;
			const T* data() const noexcept;
			void swap(Vector<T>& other);//数组交换，你变我我变你
			void resize(int newsize);
			void resize(int newsize, const T& value);
			void reserve(int n);//使容量至少大于n

			T& operator[](int index);
			const T& operator[](int index) const;
			Vector<T>& operator = (const Vector<T> & other);//赋值

			class iterator
			{
			public:
				iterator() :m_pointer(nullptr) {};
				iterator(T* pointer) :m_pointer(pointer) {};
				~iterator(){};

				bool operator ==(const iterator& other) const
				{
					return m_pointer == other.m_pointer;
				}
				bool operator !=(const iterator& other) const
				{
					return m_pointer != other.m_pointer;
				}
				iterator& operator = (const iterator& other)//这是浅拷贝（shallow copy），只涉及指针本身的赋值，而不涉及指针所指向的内存的释放或分配。
															//返回引用
				{
					if (this != &other) // 避免自赋值
					{
						m_pointer = other.m_pointer;//没有涉及 new 或 delete 操作。因此，m_pointer 在赋值时无需释放旧的指针所指向的内存，因为它不是内存的所有者，也不负责管理内存
					}
					return *this;//返回引用
				}
				//前缀++ 返回引用 效率高
				iterator& operator ++()
				{
					m_pointer += 1;
					return *this;
				}
				//后缀++ 返回副本
				iterator operator ++ (int) //需要一个无效参数"int"，起标志作用
				{
					iterator it = *this;//耗能
					++(*this);
					return it;
				}
				iterator operator + (int i)
				{
					iterator it = *this;
					it.m_pointer += i;
					return it;
				}
				iterator & operator += (int i)
				{
					m_pointer += i;
					return *this;
				}
				//前缀--
				iterator& operator -- ()
				{
					m_pointer -=1;
					return *this;
				}
				//后缀--
				iterator operator -- (int)
				{
					iterator it = *this;
					--(*this);
					return it;
				}
				iterator operator -(int i)
				{
					iterator it = *this;
					it.m_pointer -= i;
					return it;
				}
				iterator& operator -= (int i)
				{
					m_pointer -= i;
					return *this;
				}
				int operator - (const iterator& other) const
				{
					return m_pointer - other.m_pointer;
				}
				T& operator * () //迭代器解引用
				{
					return *m_pointer;
				}
				T* operator->() //指针运算
				{
					return m_pointer;
				}
			private:
				T* m_pointer;
			};
			class reverse_iterator
			{
			public:
				reverse_iterator() :m_pointer(nullptr) {};
				reverse_iterator(T *pointer) :m_pointer(pointer) {};
				~reverse_iterator(){};
				bool operator == (const reverse_iterator& other) const
				{
					return m_pointer == other.m_pointer;
				}
				bool operator != (const reverse_iterator& other) const
				{
					return m_pointer != other.m_pointer;
				}
				reverse_iterator& operator = (const reverse_iterator& other)//这是浅拷贝（shallow copy），只涉及指针本身的赋值，而不涉及指针所指向的内存的释放或分配。
					//返回引用
				{
					if (this != &other) // 避免自赋值
					{
						m_pointer = other.m_pointer;//没有涉及 new 或 delete 操作。因此，m_pointer 在赋值时无需释放旧的指针所指向的内存，因为它不是内存的所有者，也不负责管理内存
					}
					return *this;//返回引用
				}
				reverse_iterator& operator ++()//前缀++
				{
					m_pointer -= 1;
					return *this;
				}
				reverse_iterator operator ++(int)//后缀++
				{
					reverse_iterator it = *this;
					++(*this);//调用前缀++的实现
					return it;
				}
				reverse_iterator operator +(int i)
				{
					reverse_iterator it = *this;
					it.m_pointer -= i;
					return it;
				}//加法 不对当前迭代器做修改

				reverse_iterator operator +=(int i)
				{
					m_pointer -= i;
					return *this;
				}//加法赋值 对当前迭代器做修改
				//前缀--
				reverse_iterator& operator --()
				{
					m_pointer += 1;
					return *this;
				}
				//后缀--
				reverse_iterator operator --(int)
				{
					reverse_iterator it = *this;
					--(*this);
					return it;
				}
				reverse_iterator operator-(int i)
				{
					reverse_iterator it = *this;
					it.m_pointer += i;
					return it;
				}
				reverse_iterator& operator -=(int i)
				{
					m_pointer += i;
					return *this;
				}
				T& operator *()
				{
					return *m_pointer;
				}
				T* operator ->()
				{
					return m_pointer;
				}
			private:
				T* m_pointer;
			};
			iterator begin() noexcept;
			iterator end() noexcept;//最后一个元素的后面一位位置
			reverse_iterator rbegin() noexcept;
			reverse_iterator rend() noexcept;

			iterator insert(iterator pos, const T& value);
			iterator insert(iterator pos, int n,const T& value);

			iterator erase(iterator pos);
			//[first, last) 包括first，不包括last
			iterator erase(iterator first, iterator last);

		private:
			T* m_data;
			int m_size;
			int m_capacity;
		};


		//定义要放在命名空间下
		//模板类函数定义要加template <typename T>
		template <typename T>
		Vector<T>::Vector() :m_data(nullptr), m_size(0), m_capacity(0)
		{

		}

		template <typename T>
		Vector<T>::~Vector()
		{
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_size = 0;
			m_capacity = 0;
		}

		template <typename T>
		bool Vector<T>::is_basic_tpye()
		{
			if (std::is_pointer<T>::value)
			{
				return true;
			}
			return(typeid(T) == typeid(bool)) ||
				(typeid(T) == typeid(char)) ||
				(typeid(T) == typeid(unsigned char)) ||
				(typeid(T) == typeid(short)) ||
				(typeid(T) == typeid(unsigned short)) ||
				(typeid(T) == typeid(int)) ||
				(typeid(T) == typeid(unsigned int)) ||
				(typeid(T) == typeid(long)) ||
				(typeid(T) == typeid(unsigned long)) ||
				(typeid(T) == typeid(float)) ||
				(typeid(T) == typeid(double));
		}

		template <typename T>
		void Vector<T>::push_back(const T& value)
		{
			if (m_size < m_capacity)
			{
				m_data[m_size] = value;
				m_size++;
				return;
			}
			//vector 扩容算法
			if (m_capacity == 0)
			{
				m_capacity = 1;
			}
			else
			{
				m_capacity *= 2;
			}
			T* data = new T[m_capacity];//扩容后分配新内存
			//优化前--开始
			//for (int i = 0; i < m_size; i++)
			//{
			//	data[i] = m_data[i];
			//}
			//优化前--结束

			//优化后--开始
			if (is_basic_tpye())//判断模板参数类型
			{
				std::memcpy(data, m_data, m_size * sizeof(T));
			}
			else
			{
				for (int i = 0; i < m_size; i++)
				{
					data[i] = m_data[i];
				}
			}
			//优化后--结束

			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_data = data;
			m_data[m_size] = value;
			m_size++;
		}
	
		template <typename T>
		void Vector<T>::pop_back()//不需要真的删除这个元素，只需要减小m_size
		{
			if (m_size > 0)
			{
				m_size--;
			}
			
		}

		template <typename T>
		void Vector<T>::show()const
		{
			std::cout << "size=" << m_size << ", capacity=" << m_capacity << std::endl;
			for (int i = 0; i < m_size; i++)
			{
				std::cout << m_data[i] << ", ";
			}
			std::cout << std::endl;
		}
		
		template <typename T>
		T& Vector<T>::at(int index)
		{
			if (index < 0 || index >= m_size)
			{
				throw std::logic_error("out of rage");
			}
			return m_data[index];
		};

		template <typename T>
		const T& Vector<T>::at(int index) const
		{
			return at(index);
		};

		template <typename T>
		T& Vector<T>::front()
		{
			if (m_size <= 0)
			{
				throw std::logic_error("vector is enmpty");
			}
			return m_data[0];
		}

		template <typename T>
		const T& Vector<T>::front() const
		{

			return front();
		}

		template <typename T>
		T& Vector<T>::back()
		{
			if (m_size <= 0)
			{
				throw std::logic_error("vector is enmpty");
			}
			return m_data[m_size-1];
		}

		template <typename T>
		const T& Vector<T>::back() const
		{

			return back();
		}

		template <typename T>
		bool Vector<T>::empty() const noexcept
		{
			return m_size == 0;
		}

		template <typename T>
		void Vector<T>::clear() noexcept
		{
			m_size = 0;
		}

		template <typename T>
		int Vector<T>::size() const noexcept
		{
			return m_size;
		}

		template <typename T>
		int Vector<T>::capacity() const noexcept
		{
			return m_capacity;
		}

		template <typename T>
		T* Vector<T>::data() noexcept
		{
			return m_data;
		}

		template <typename T>
		const T* Vector<T>::data() const noexcept
		{
			return data();
		};

		template <typename T>
		T& Vector<T>::operator[](int index)
		{
			return at(index);
		}

		template <typename T>
		const T& Vector<T>::operator[](int index) const
		{
			return at(index);
		};

		template <typename T>
		Vector<T>& Vector<T>::operator = (const Vector<T> &other)
		{
			if (m_capacity < other.m_size)
			{
				if (m_data != nullptr)
				{
					delete[] m_data;
					m_data = nullptr;
					m_size = 0;
					m_capacity = 0;
				}
				while (m_capacity < other.m_size)
				{
					//扩容
					if (m_capacity == 0)
					{
						m_capacity = 1;
					}
					else
					{
						m_capacity *= 2;
					}
				}
				m_data = new T[m_capacity];//创建新内存
			}
			//拷贝进新数组
			for (int i = 0; i < other.m_size; i++)
			{
				m_data[i] = other.m_data[i];
			}
			m_size = other.m_size;
			return *this;
		};//赋值

		template <typename T>
		void Vector<T>::swap(Vector<T>& other)
		{
			T* data = other.m_data;
			int size = other.m_size;
			int capacity = other.m_capacity;

			other.m_data = m_data;
			other.m_size = m_size;
			other.m_capacity = m_capacity;

			m_data = data;
			m_size = size;
			m_capacity = capacity;
		};

		template <typename T>
		void Vector<T>::resize(int newsize)
		{
			if (newsize < m_size)
			{
				m_size = newsize;//多的部分失去索引
				return;
			}
			//
			if (newsize <= m_capacity && newsize > m_size)
			{
				for (int i = m_size; i < newsize; i++)
				{
					m_data[i] = T();
				}
				m_size = newsize;
				return;
			}
			//
			while (newsize>m_capacity)
			{
				if (m_capacity == 0)
				{
					m_capacity = 1;
				}
				else
				{
					m_capacity *= 2;
				}
			}
			T* data = new T[m_capacity];//data是局部指针变量，data本身在函数结束后销毁，但data指向的内存通过后续的操作被m_data指向
			for (int i = 0; i < m_size; i++)
			{
				data[i] = m_data[i];
			}
			for (int i = m_size; i < newsize; i++)
			{
				data[i] = T();
			}
			if (m_data != nullptr)
			{
				delete[] m_data;//先释放旧指向的内存。若不释放，则原m_data指向的内存丢失指针，无法被访问无法被释放，造成内存泄漏
				m_data = nullptr;//防止野指针
			}
			m_data = data;
			m_size = newsize;
		}

		template <typename T>
		void Vector<T>::resize(int newsize, const T& value)
		{
			if (newsize < m_size)
			{
				m_size = newsize;//多的部分失去索引
				return;
			}
			//
			if (newsize <= m_capacity && newsize > m_size)
			{
				for (int i = m_size; i < newsize; i++)
				{
					m_data[i] = value;
				}
				m_size = newsize;
				return;
			}
			//
			while (newsize > m_capacity)
			{
				if (m_capacity == 0)
				{
					m_capacity = 1;
				}
				else
				{
					m_capacity *= 2;
				}
			}
			T* data = new T[m_capacity];
			for (int i = 0; i < m_size; i++)
			{
				data[i] = m_data[i];
			}
			for (int i = m_size; i < newsize; i++)
			{
				data[i] = value;
			}
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_data = data;
			m_size = newsize;
		}

		template <typename T>
		void Vector<T>::reserve(int n)
		{
			if (m_capacity >= n)
			{
				return;
			}
			while (m_capacity < n)
			{
				if (m_capacity == 0)
				{
					m_capacity = 1;
				}
				else
				{
					m_capacity *= 2;
				}
			}
			T* data = new T[m_capacity];
			for (int i = 0; i < m_size; i++)
			{
				data[i] = m_data[i];
			}
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_data = data;

		}

		template <typename T>
		typename Vector<T>::iterator Vector<T>::begin() noexcept//C++要求在模板中，当使用依赖于模板参数的类型时，必须在其前面加上 typename 关键字来明确表明这是一个类型。
		{
			Vector<T>::iterator it(m_data);
			return it;
		}
		template <typename T>
		typename Vector<T>::iterator Vector<T>::end() noexcept
		{
			Vector<T>::iterator it(m_data+m_size);//最后一个元素的后面一位位置
			return it;
		}
		template <typename T>
		typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
		{
			Vector<T>::reverse_iterator it(m_data + m_size - 1);
			return it;
		}
		template <typename T>
		typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
		{
			 Vector<T>::reverse_iterator it(m_data-1);
			return it;
		}

		template <typename T>
		typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& value)
		{
			return insert(pos, 1, value);
		}
		template <typename T>
		typename Vector<T>::iterator Vector<T>::insert(iterator pos, int n, const T& value)//没有处理，pos在m_size外的情况？
		{
			int size = pos - begin();//插入位置迭代器-初始位置迭代器=数组下标
			if (m_size + n <= m_capacity)//插入后容量够否
			{
				//先把后面元素往后挪，避免覆盖
				for (int i = m_size; i > size; i--)
				{
					m_data[i + n - 1] = m_data[i - 1];
				}
				//插入新值
				for (int i = 0; i < n; i++)
				{
					m_data[size + i] = value;
				}
				//前面元素不动
				m_size += n;
				return Vector<T>::iterator(m_data + size);
			}
			//需要扩容
			while (m_size + n > m_capacity)
			{
				if (m_capacity == 0)
				{
					m_capacity = 1;
				}
				else
				{
					m_capacity *= 2;
				}
			}
			T* data = new T[m_capacity];
			//前部分旧数据
			for (int i = 0; i < size; i++)
			{
				data[i] = m_data[i];
			}
			//插入新值
			for (int i = 0; i < n; i++)
			{
				data[size + i] = value;
			}
			//后面部分旧值后挪
			for (int i = size; i < m_size; i++)
			{
				data[i + n] = m_data[i];
			}
			if (m_data != nullptr)
			{
				delete[] m_data;
				m_data = nullptr;
			}
			m_data = data;
			m_size += n;
			return Vector<T>::iterator(m_data + size);
		}
		template <typename T>
		typename Vector<T>::iterator Vector<T>::erase(iterator pos)
		{
			if (pos == end())
			{
				throw std::logic_error("out of range");
			}
			if (end() - pos == 1)
			{
				//删除最后一个元素，其他元素不动
				m_size -= 1;
				return end();
			}
			int size = pos - begin();//下标
			for (int i = size; i < m_size - 1; i++)
			{
				m_data[i] = m_data[i + 1];
			}
			m_size -= 1;
			return pos;
		}
		template <typename T>
		typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last)
		{
			int f = first - begin();//first对应数组下标
			int l = last - begin();//last对应数组下标
			int n = last - first;
			for (int i = 0; i < m_size - l; i++)
			{
				m_data[f + i] = m_data[l + i];
			}
			m_size -= n;
			return first;
		}
	}
}


