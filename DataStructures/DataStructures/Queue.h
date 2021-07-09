#pragma once

namespace DataStructures
{
	template <typename T>
	struct QueueElement
	{
		T data;
		QueueElement* prev;
		QueueElement* next;

		QueueElement()
			: data(T()), prev(nullptr), next(nullptr)
		{
		}

		QueueElement(const T& data)
			: data(data), prev(nullptr), next(nullptr)
		{
		}

		QueueElement(T&& data)
			: data(std::move(data)), prev(nullptr), next(nullptr)
		{
		}
		template <typename ...Args>
		QueueElement(Args&&... args)
			: data(std::forward<Args>(args)...), prev(nullptr), next(nullptr)
		{

		}
	};

	template <typename T>
	class Queue
	{
	public:
		using DataType = T;

		using Element = QueueElement<T>;

	private:
		Element* m_Front = nullptr;
		Element* m_Back = nullptr;

		size_t m_Size;

	private:
		void PutNextToEachOther(Element* left, Element* right)
		{
			right->prev = left;
			left->next = right;
		}

	public:

		Queue()
		{

		}

		Queue(const Queue& other)
		{
			Element* current = other.m_Front;
			for (size_t i = 0; i < other.m_Size; i++)
			{
				Push(current->data);
				current = current->next;
			}
			m_Size = other.m_Size;
		}

		Queue(Queue&& other) noexcept
		{
			m_Front = other.m_Front;
			m_Back = other.m_Back;
			m_Size = other.m_Size;

			other.m_Back = nullptr;
			other.m_Front = nullptr;
			other.m_Size = 0;
		}

		~Queue()
		{
			Clear();
		}

		void Push(const DataType& newData)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(newData);
				m_Front = m_Back;
			}
			else
			{
				Element* newTop = new Element(newData);
				PutNextToEachOther(m_Back, newTop);
				m_Back = newTop;
			}
			m_Size++;
		}

		void Push(DataType&& newData)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(std::move(newData));
				m_Front = m_Back;
			}
			else
			{
				Element* newTop = new Element(std::move(newData));
				PutNextToEachOther(m_Back, newTop);
				m_Back = newTop;
			}
			m_Size++;
		}

		template <typename ...Args>
		DataType& Emplace(Args&&... args)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(args...);
				m_Front = m_Back;
			}
			else
			{
				Element* newTop = new Element(args...);
				PutNextToEachOther(m_Back, newTop);
				m_Back = newTop;
			}
			m_Size++;

			return m_Back->data;
		}

		void Pop()
		{
			if (m_Size == 1)
			{
				delete m_Front;

				m_Back = nullptr;
				m_Front = nullptr;
			}
			else
			{
				Element* elementToDelete = m_Front;
				m_Front = m_Front->next;
				m_Front->prev = nullptr;

				delete elementToDelete;
			}
			m_Size--;
		}

		void Clear()
		{
			if (m_Size == 0)
				return;

			Element* current = m_Front;
			Element* elementToDelete = nullptr;
			for (size_t i = 0; i < m_Size; i++)
			{
				elementToDelete = current;
				current = current->next;
				delete elementToDelete;
			}
			m_Size = 0;

			m_Back = nullptr;
			m_Front = nullptr;
		}

		Queue& operator=(const Queue& other)
		{
			Clear();
			Element* current = m_Front;
			for (size_t i = 0; i < m_Size; i++)
			{
				PushBack(current->data);
				current = current->next;
			}
			m_Size = other.m_Size;

			return *this;
		}

		Queue& operator=(Queue&& other) noexcept
		{
			Clear();
			m_Front = other.m_Front;
			m_Back = other.m_Back;
			m_Size = other.m_Size;

			other.m_Back = nullptr;
			other.m_Front = nullptr;
			other.m_Size = 0;

			return *this;
		}

		DataType& Back() { return m_Back->data; }
		const DataType& Back() const { return m_Back->data; }

		DataType& Front() { return m_Front->data; }
		const DataType& Front() const { return m_Front->data; }

		bool IsEmpty() const { return m_Size == 0; }

		size_t Size() const { return m_Size; }
	};
}