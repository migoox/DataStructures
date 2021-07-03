#pragma once

namespace DataStructures
{
	template<typename T>
	struct Element
	{
		Element<T>* prev;
		Element<T>* next;
		T data;
	};

	template<typename T>
	class LStack
	{
	private:
		Element<T>* m_eTop;
		Element<T>* m_eBegin;

		size_t m_sSize;

	private:
		void Cpy(const LStack& other) // copy data to lstack from other
		{
			if (other.m_sSize == 0)
				return;

			Element<T>* temp = other.m_eBegin;

			push(temp->data);
			for (size_t i = 0; i < other.m_eSize - 1; i++)
			{
				temp = temp->next;
				push(temp->data);
			}

			temp = nullptr;
		}

		void Move(LStack&& other) // move data to lstack from other
		{
			if (other.m_Size == 0)
				return;

			m_sSize = other.m_sSize;
			m_eBegin = other.m_eBegin;
			m_eTop = other.m_eTop;

			other.m_sSize = 0;
			other.m_eBegin = nullptr;
			other.m_eTop = nullptr;
		}

		void Clear() // delete all data
		{
			Element<T>* previousElement;
			for (size_t i = 0; i < m_sSize; i++)
			{
				previousElement = m_eTop->prev;
				delete m_eTop;
				m_eTop = previousElement;
			}
			m_sSize = 0;
		}
	public:
		LStack() // default constructor
		{ 
			m_sSize = 0;
			m_eTop = nullptr; 
			m_eBegin = nullptr;
		}

		LStack(const LStack& other) // copy constructor
		{
			m_sSize = 0;
			m_eTop = nullptr;
			m_eBegin = nullptr;
			Cpy(other);
		}

		LStack(LStack&& other) noexcept // move constructor
		{
			m_sSize = 0;
			m_eTop = nullptr;
			m_eBegin = nullptr;
			Move(std::move(other));
		}

		~LStack() // destructor
		{ 
			if (m_sSize == 0)
				return;

			Clear();
		}

		void Push(const T& newData) // push on top
		{
			if (m_sSize == 0)
			{
				m_eTop = new Element<T>;
				m_eTop->data = newData;
				m_eTop->next = nullptr;
				m_eTop->prev = nullptr;

				m_eBegin = m_eTop;
			}
			else
			{
				Element<T>* oldTop = m_eTop;

				m_eTop = new Element<T>;

				oldTop->next = m_eTop;

				m_eTop->data = newData;
				m_eTop->next = nullptr;
				m_eTop->prev = oldTop;
			}
			m_sSize++;
		}

		void Push(T&& newData) // push on top for r-values
		{
			if (m_sSize == 0)
			{
				m_eTop = new Element<T>;
				m_eTop->data = std::move(newData);
				m_eTop->next = nullptr;
				m_eTop->prev = nullptr;

				m_eBegin = m_eTop;
			}
			else
			{
				Element<T>* oldTop = m_eTop;

				m_eTop = new Element<T>;

				oldTop->next = m_eTop;

				m_eTop->data = std::move(newData);
				m_eTop->next = nullptr;
				m_eTop->prev = oldTop;
			}
			m_sSize++;
		}

		bool Pop() // pop top
		{
			if (m_sSize == 0)
				return false;

			if (m_sSize == 1)
			{
				delete m_eTop;
				m_eTop = nullptr;
			}
			else
			{
				Element<T>* previousElement = m_eTop->prev;
				delete m_eTop;

				m_eTop = previousElement;
				m_eTop->next = nullptr;
			}

			m_sSize--;

			return true;
		}

		T& Top() // get top
		{
			return m_eTop->data;
		}

		int Size() // get size of lstack
		{
			return m_sSize;
		}
		
		bool IsEmpty() // returns true in case that stack is empty
		{
			if (m_sSize == 0)
				return true;

			return false;
		}

		LStack& operator=(const LStack& other) // copy assignment
		{
			if (this != &other)
			{
				Clear();
				Cpy(other);
			}
			return *this;
		}

		LStack& operator=(LStack&& other) noexcept // move assignment
		{
			if (this != &other)
			{
				Clear();
				Move(std::move(other));
			}
			return *this;
		}

		friend std::ostream& operator<<(std::ostream& os, const LStack& other) // stream friend
		{
			if (other.m_sSize == 0)
			{
				os << "LSTACK IS EMPTY\n";
				return os;
			}

			Element<T>* temp = other.m_eTop;

			os << temp->data << "\n";
			for (size_t i = 0; i < other.m_sSize - 1; i++)
			{
				temp = temp->prev;
				os << temp->data << "\n";
			}

			return os;
		}
	};
}