#pragma once

namespace DataStructures
{
	template<typename T>
	struct ListElement
	{
		ListElement<T>* prev;
		ListElement<T>* next;
		T data;
	};

	template<typename T>
	class List
	{
	private:
		ListElement<T>* m_eBegin;
		ListElement<T>* m_eEnd;

		size_t m_sSize;
	
	private:
		void Cpy()
		{

		}

		void Move()
		{

		}
	public:
		List() // default constructor
		{
			m_sSize = 0;
			m_eBegin = nullptr;
			m_eEnd = nullptr;
		}

		List(const List& other) // copy constructor
		{
			m_sSize = 0;
			m_eBegin = nullptr;
			m_eEnd = nullptr;
			Cpy(other);
		}

		List(List&& other) noexcept // move constructor
		{
			m_sSize = 0;
			m_eBegin = nullptr;
			m_eEnd = nullptr;
			Move(std::move(other));
		}

		~List() // destructor
		{
			if (m_sSize == 0)
				return;

			Clear();
		}

		void PushBack(const T& newData)
		{
			if (m_sSize == 0)
			{
				m_eEnd = new ListElement<T>;
				m_eEnd->data = newData;
				m_eEnd->next = nullptr;
				m_eEnd->prev = nullptr;

				m_eBegin = m_eEnd;
			}
			else
			{
				ListElement<T>* oldEnd = m_eEnd;

				m_eEnd = new ListElement<T>;

				oldEnd->next = m_eEnd;

				m_eEnd->data = newData;
				m_eEnd->next = nullptr;
				m_eEnd->prev = oldEnd;
			}
			m_sSize++;
		}

		void PushFront(const T& newData)
		{
			if (m_sSize == 0)
			{
				m_eEnd = new ListElement<T>;
				m_eEnd->data = newData;
				m_eEnd->next = nullptr;
				m_eEnd->prev = nullptr;

				m_eBegin = m_eEnd;
			}
			else
			{
				ListElement<T>* oldBegin = m_eBegin;

				m_eBegin = new ListElement<T>;

				oldBegin->prev = m_eBegin;

				m_eBegin->data = newData;
				m_eBegin->next = oldBegin;
				m_eBegin->prev = nullptr;
			}
			m_sSize++;
		}

		bool PopBack()
		{
			if (m_sSize == 0)
				return false;

			if (m_sSize == 1)
			{
				delete m_eEnd;
				m_eEnd = nullptr;
				m_eBegin = nullptr;
			}
			else
			{
				ListElement<T>* previousElement = m_eEnd->prev;
				delete m_eEnd;

				m_eEnd = previousElement;
				m_eEnd->next = nullptr;
			}

			m_sSize--;

			return true;
		}

		bool PopFront()
		{
			if (m_sSize == 0)
				return false;

			if (m_sSize == 1)
			{
				delete m_eEnd;
				m_eEnd = nullptr;
				m_eBegin = nullptr;
			}
			else
			{
				ListElement<T>* nextElement = m_eBegin->next;
				delete m_eBegin;

				m_eBegin = nextElement;
				m_eBegin->prev = nullptr;
			}

			m_sSize--;

			return true;
		}

		void RemoveAt(int index)
		{
			if (index >= m_sSize)
				return;

			if (m_sSize == 1)
			{
				delete m_eEnd;
				m_eEnd = nullptr;
				m_eBegin = nullptr;
			}

			if (index == m_sSize - 1)
			{
				PopBack();
			}
			else if (index == 0)
			{
				PopFront();
			}
			else
			{
				ListElement<T>* element;
				element = m_eBegin;
				for (size_t i = 0; i < index; i++)
				{
					element = element->next;
				}

				element->next->prev = element->prev;
				element->prev->next = element->next;

				delete element;

				m_sSize--; 
			}
		}

		void Remove(const T& data)
		{
			if (m_sSize == 1)
			{
				if (m_eEnd->data == data)
				{
					delete m_eEnd;
					m_eEnd = nullptr;
					m_eBegin = nullptr;
					m_sSize--;
				}
				return;
			}

			ListElement<T>* element = m_eBegin;
			ListElement<T>* currentElement;

			int size = m_sSize;

			for (size_t i = 0; i < size; i++)
			{
				currentElement = element;
				element = element->next;

				if (currentElement->data == data)
				{
					if (currentElement == m_eBegin)
					{
						PopFront();
					}
					else if (currentElement == m_eEnd)
					{
						PopBack();
					}
					else
					{
						currentElement->next->prev = currentElement->prev;
						currentElement->prev->next = currentElement->next;

						delete currentElement;

						m_sSize--;
					}
				}
			}
		}

		int Size()
		{
			return m_sSize;
		}

		void Clear()
		{
			ListElement<T>* previousElement;
			for (size_t i = 0; i < m_sSize; i++)
			{
				previousElement = m_eEnd->prev;
				delete m_eEnd;
				m_eEnd = previousElement;
			}
			m_sSize = 0;
		}

		T& operator[](int index)
		{
			ListElement<T>* element;

			element = m_eBegin;
			for (size_t i = 0; i < index; i++)
			{
				element = element->next;
			}

			return element->data;
		}

		friend std::ostream& operator<<(std::ostream& os, const List& other) // stream friend
		{
			if (other.m_sSize == 0)
			{
				os << "LIST IS EMPTY\n";
				return os;
			}

			ListElement<T>* temp = other.m_eEnd;

			os << "[" << other.m_sSize - 1 << "]: " << temp->data << "\n";
			for (size_t i = 0; i < other.m_sSize - 1; i++)
			{
				temp = temp->prev;
				os << "["<< other.m_sSize - i - 2 << "]: " << temp->data << "\n";
			}

			return os;
		}
	};
}