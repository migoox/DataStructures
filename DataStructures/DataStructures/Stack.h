#pragma once

namespace DataStructures
{
	template <typename T>
	struct StackElement
	{
		T data;
		StackElement* prev;
		StackElement* next;

		StackElement()
			: data(T()), prev(nullptr), next(nullptr)
		{
		}

		StackElement(const T& data)
			: data(data), prev(nullptr), next(nullptr)
		{
		}

		StackElement(T&& data)
			: data(std::move(data)), prev(nullptr), next(nullptr)
		{
		}
		template <typename ...Args>
		StackElement(Args&&... args)
			: data(std::forward<Args>(args)...), prev(nullptr), next(nullptr)
		{

		}
	};

	template <typename T>
	class Stack
	{
	public:
		using DataType = T;

		using Element = StackElement<T>;


	private:
		Element* m_Bottom = nullptr;
		Element* m_Top = nullptr;

		size_t m_Size;

	private:
		void PutNextToEachOther(Element* down, Element* up)
		{
			up->prev = down;
			down->next = up;
		}

	public:
		
		Stack()
		{

		}

		Stack(const Stack& other)
		{
			Element* current = other.m_Bottom;
			for (size_t i = 0; i < other.m_Size; i++)
			{
				Push(current->data);
				current = current->next;
			}
			m_Size = other.m_Size;
		}

		Stack(Stack&& other) noexcept 
		{
			m_Bottom = other.m_Bottom;
			m_Top = other.m_Top;
			m_Size = other.m_Size;

			other.m_Top = nullptr;
			other.m_Bottom = nullptr;
			other.m_Size = 0;
		}

		~Stack()
		{
			Clear();
		}

		void Push(const DataType& newData)
		{
			if (m_Size == 0)
			{
				m_Top = new Element(newData);
				m_Bottom = m_Top;
			}
			else
			{
				Element* newTop = new Element(newData);
				PutNextToEachOther(m_Top, newTop);
				m_Top = newTop;
			}
			m_Size++;
		}

		void Push(DataType&& newData)
		{
			if (m_Size == 0)
			{
				m_Top = new Element(std::move(newData));
				m_Bottom = m_Top;
			}
			else
			{
				Element* newTop = new Element(std::move(newData));
				PutNextToEachOther(m_Top, newTop);
				m_Top = newTop;
			}
			m_Size++;
		}

		template <typename ...Args>
		DataType& Emplace(Args&&... args)
		{
			if (m_Size == 0)
			{
				m_Top = new Element(args...);
				m_Bottom = m_Top;
			}
			else
			{
				Element* newTop = new Element(args...);
				PutNextToEachOther(m_Top, newTop);
				m_Top = newTop;
			}
			m_Size++;

			return m_Top->data;
		}

		void Pop()
		{
			if (m_Size == 1)
			{
				delete m_Top;

				m_Top = nullptr;
				m_Bottom = nullptr;
			}
			else
			{
				Element* elementToDelete = m_Top;
				m_Top = m_Top->prev;
				m_Top->next = nullptr;

				delete elementToDelete;
			}
			m_Size--;
		}

		void Clear()
		{
			if (m_Size == 0)
				return;

			Element* current = m_Bottom;
			Element* elementToDelete = nullptr;
			for (size_t i = 0; i < m_Size; i++)
			{
				std::cout << current->data.x << std::endl;
				elementToDelete = current;
				current = current->next;
				delete elementToDelete;
			}
			m_Size = 0;

			m_Top = nullptr;
			m_Bottom = nullptr;
		}

		Stack& operator=(const Stack& other)
		{
			Clear();
			Element* current = m_Bottom;
			for (size_t i = 0; i < m_Size; i++)
			{
				PushBack(current->data);
				current = current->next;
			}
			m_Size = other.m_Size;

			return *this;
		}
		
		Stack& operator=(Stack&& other) noexcept
		{
			Clear();
			m_Bottom = other.m_Bottom;
			m_Top = other.m_Top;
			m_Size = other.m_Size;

			other.m_Top = nullptr;
			other.m_Bottom = nullptr;
			other.m_Size = 0;
			
			return *this;
		}

		DataType& Top() { return m_Top->data; }
		const DataType& Top() const { return m_Top->data; }

		bool IsEmpty() const { return m_Size == 0; }

		size_t Size() const { return m_Size; }
	};
}