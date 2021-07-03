#pragma once

namespace DataStructures
{
	template<class T, const size_t _MaxSize>
	class Stack
	{
	private:
		T* m_Data;
		size_t m_Size;

		void cpy(const Stack& other)
		{
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i] = other.m_Data[i];
		}
	public:
		Stack() // default constructor
		{ 
			m_Data = new T[_MaxSize];
			m_Size = 0;
		} 

		Stack(const Stack& other) // copy constructor
		{
			m_Data = new T[_MaxSize];
			m_Size = other.m_Size;

			cpy(other);
		}

		Stack(Stack&& other) noexcept // move constructor
		{
			m_Data = other.m_Data;
			m_Size = other.m_Size;

			other.m_Size = 0;
			other.m_Data = nullptr;
		}

		~Stack() // destructor
		{ 
			delete[] m_Data; 
		}

		bool push(const T& element) // push to stack
		{
			if (isFull())
				return false;

			m_Data[m_Size] = element;
			m_Size++;

			return true;
		}

		bool pop() // pop from stack
		{
			if (isEmpty())
				return false;

			m_Size--;

			return true;
		}

		T& top() // get acces to the adress of top
		{
			return m_Data[m_Size - 1];
		}

		int size() // get current amount of data stored
		{
			return m_Size;
		}

		int maxSize() // get maximum amount of data that can be stored
		{
			return _MaxSize;
		}

		bool isEmpty() // returns true in case that stack is empty
		{
			if (m_Size == 0)
				return true;

			return false;
		}

		bool isFull() // returns true in case that stack is full
		{
			if (m_Size == _MaxSize)
				return true;

			return false;
		}

		Stack& operator=(const Stack& other) 
		{
			if (this != &other) 
			{
				m_Size = other.m_Size;

				cpy(other);
			}
			return *this;
		}

		Stack& operator=(Stack&& other) noexcept
		{
			if (this != &other)
			{
				delete[] m_Data; 

				m_Size = other.m_Size;
				m_Data = other.m_Data;

				other.m_Size = 0;
				other.m_Data = nullptr;
			}
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const Stack& other)
		{
			if (other.m_Size == 0)
			{
				os << "STACK IS EMPTY\n";
				return os;
			}

			for (size_t i = 0; i < other.m_Size; i++)
			{
				os << other.m_Data[i] << "\n";
			}


			return os;
		}
	};
}