#pragma once
namespace DataStructures
{
	template <typename T>
	struct ListElement
	{
		T data;
		ListElement* prev;
		ListElement* next;

		ListElement()
			: data(T()), prev(nullptr), next(nullptr)
		{
		}

		ListElement(const T& data)
			: data(data), prev(nullptr), next(nullptr)
		{
		}

		ListElement(T&& data)
			: data(std::move(data)), prev(nullptr), next(nullptr)
		{
		}

		ListElement(const T& data, ListElement* left, ListElement* right)
			: data(data), prev(left), next(right)
		{
			prev->next = this;
			next->prev = this;
		}

		ListElement(T&& data, ListElement* left, ListElement* right)
			: data(std::move(data)), prev(left), next(right)
		{
			prev->next = this;
			next->prev = this;
		}

		template <typename ...Args>
		ListElement(ListElement* left, ListElement* right, Args&&... args)
			: data(std::forward<Args>(args)...), prev(left), next(right)
		{
			prev->next = this;
			next->prev = this;
		}
	};

	template <typename MyList>
	class ListConstIterator
	{
	public:
		using DataType = typename MyList::DataType;

		using Element = ListElement<DataType>;

		using PointerElement = Element*;
		using ConstPointerElement = const Element*;
		using ReferenceElement = Element&;
		using ConstReferenceElement = const Element&;

		using PointerType = DataType*;
		using ConstPointerType = const DataType*;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;

	private:
		ConstPointerElement m_Ptr;

	public:
		ListConstIterator() noexcept
			: m_Ptr(nullptr)
		{
		}

		explicit ListConstIterator(ConstPointerElement ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		ListConstIterator(const ListConstIterator& other) noexcept
			: m_Ptr(other.m_Ptr)
		{
		}

		ConstPointerType operator->() const
		{
			return &m_Ptr->data;
		}

		ConstReferenceType operator*() const
		{
			return m_Ptr->data;
		}

		ConstReferenceType operator[](size_t index)
		{
			PointerElement temp = m_Ptr + index;
			return temp->data;
		}

		ListConstIterator operator++()
		{
			m_Ptr = m_Ptr->next;
			return *this;
		}

		ListConstIterator operator++(int)
		{
			ListConstIterator temp = *this;
			m_Ptr = m_Ptr->next;
			return temp;
		}

		ListConstIterator operator--()
		{
			m_Ptr = m_Ptr->prev;
			return *this;
		}

		ListConstIterator operator--(int)
		{
			ListConstIterator temp = *this;
			m_Ptr = m_Ptr->prev;
			return temp;
		}

		ListConstIterator operator+=(size_t right)
		{
			for (size_t i = 0; i < right; i++)
			{
				m_Ptr = m_Ptr->next;
			}
			return *this;
		}

		ListConstIterator operator-=(size_t right)
		{
			for (size_t i = 0; i < right; i++)
			{
				m_Ptr = m_Ptr->prev;
			}
			return *this;
		}

		ListConstIterator operator+(size_t right)
		{
			ListConstIterator temp = *this;
			for (size_t i = 0; i < right; i++)
			{
				temp.m_Ptr = temp.m_Ptr->next;
			}
			return temp;
		}

		ListConstIterator operator-(size_t right)
		{
			ListConstIterator temp = *this;
			for (size_t i = 0; i < right; i++)
			{
				temp.m_Ptr = temp.m_Ptr->prev;
			}
			return temp;
		}

		size_t operator-(const ListConstIterator& right)
		{
			return m_Ptr - right.m_Ptr;
		}

		ListConstIterator& operator=(const ListConstIterator& other)
		{
			if (m_Ptr != other.m_Ptr)
			{
				m_Ptr = other.m_Ptr;
			}
			return *this;
		}

		ListConstIterator& operator=(ConstPointerElement ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		ListConstIterator& operator=(PointerElement ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const ListConstIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ListConstIterator& other)
		{
			return !(m_Ptr == other.m_Ptr);
		}

		ConstPointerElement GetElement()
		{
			return m_Ptr;
		}
	};
	
	template <typename MyList>
	class ListIterator : public ListConstIterator<MyList>
	{
	public:
		using DataType = typename MyList::DataType;

		using Element = ListElement<DataType>;

		using PointerElement = Element*;
		using ReferenceElement = Element&;

		using PointerType = DataType*;
		using ReferenceType = DataType&;

		using MyBase = ListConstIterator<MyList>;

		using MyBase::MyBase;
	public:
		ReferenceType operator*()
		{
			return const_cast<ReferenceType>(MyBase::operator*());
		}

		ReferenceType operator[](size_t index)
		{
			return const_cast<ReferenceType>(MyBase::operator[](index));
		}

		PointerType operator->() noexcept
		{
			return const_cast<PointerType>(MyBase::operator->());
		}

		ListIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		ListIterator operator++(int)
		{
			ListIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		ListIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		ListIterator operator--(int)
		{
			ListIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		ListIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		ListIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		ListIterator operator+(size_t right)
		{
			return ListIterator(MyBase::operator+(right).GetElement());
		}

		ListIterator operator-(size_t right)
		{
			return ListIterator(MyBase::operator-(right).GetElement());
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const ListIterator& right)
		{
			return MyBase::operator-(right);
		}

		ListIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}

		PointerElement GetElement()
		{
			return const_cast<PointerElement>(MyBase::GetElement());
		}
	};

	template <typename MyList>
	class ListConstReversedIterator
	{
	public:
		using DataType = typename MyList::DataType;

		using Element = ListElement<DataType>;

		using PointerElement = Element*;
		using ConstPointerElement = const Element*;
		using ReferenceElement = Element&;
		using ConstReferenceElement = const Element&;

		using PointerType = DataType*;
		using ConstPointerType = const DataType*;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;

	private:
		ConstPointerElement m_Ptr;

	public:
		ListConstReversedIterator() noexcept
			: m_Ptr(nullptr)
		{
		}

		explicit ListConstReversedIterator(ConstPointerElement ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		ListConstReversedIterator(const ListConstReversedIterator& other) noexcept
			: m_Ptr(other.m_Ptr)
		{
		}

		ConstPointerType operator->() const
		{
			return &m_Ptr->data;
		}

		ConstReferenceType operator*() const
		{
			return m_Ptr->data;
		}

		ConstReferenceType operator[](size_t index)
		{
			PointerElement temp = m_Ptr - index;
			return temp->data;
		}

		ListConstReversedIterator operator++()
		{
			m_Ptr = m_Ptr->prev;
			return *this;
		}

		ListConstReversedIterator operator++(int)
		{
			ListConstReversedIterator temp = *this;
			m_Ptr = m_Ptr->prev;
			return temp;
		}

		ListConstReversedIterator operator--()
		{
			m_Ptr = m_Ptr->next;
			return *this;
		}

		ListConstReversedIterator operator--(int)
		{
			ListConstReversedIterator temp = *this;
			m_Ptr = m_Ptr->next;
			return temp;
		}

		ListConstReversedIterator operator+=(size_t right)
		{
			for (size_t i = 0; i < right; i++)
			{
				m_Ptr = m_Ptr->prev;
			}
			return *this;
		}

		ListConstReversedIterator operator-=(size_t right)
		{
			for (size_t i = 0; i < right; i++)
			{
				m_Ptr = m_Ptr->next;
			}
			return *this;
		}

		ListConstReversedIterator operator+(size_t right)
		{
			ListConstReversedIterator temp = *this;
			for (size_t i = 0; i < right; i++)
			{
				temp.m_Ptr = temp.m_Ptr->prev;
			}
			return temp;
		}

		ListConstReversedIterator operator-(size_t right)
		{
			ListConstReversedIterator temp = *this;
			for (size_t i = 0; i < right; i++)
			{
				temp.m_Ptr = temp.m_Ptr->next;
			}
			return temp;
		}

		size_t operator-(const ListConstReversedIterator& right)
		{
			return m_Ptr - right.m_Ptr;
		}

		ListConstReversedIterator& operator=(const ListConstReversedIterator& other)
		{
			if (m_Ptr != other.m_Ptr)
			{
				m_Ptr = other.m_Ptr;
			}
			return *this;
		}

		ListConstReversedIterator& operator=(ConstPointerElement ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		ListConstReversedIterator& operator=(PointerElement ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const ListConstReversedIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ListConstReversedIterator& other)
		{
			return !(m_Ptr == other.m_Ptr);
		}

		const Element* GetElement()
		{
			return m_Ptr;
		}
	};

	template <typename MyList>
	class ListReversedIterator : public ListConstReversedIterator<MyList>
	{
	public:
		using DataType = typename MyList::DataType;

		using Element = ListElement<DataType>;

		using PointerElement = Element*;
		using ReferenceElement = Element&;

		using PointerType = DataType*;
		using ReferenceType = DataType&;

		using MyBase = ListConstReversedIterator<MyList>;

		using MyBase::MyBase;
	public:
		ReferenceType operator*()
		{
			return const_cast<ReferenceType>(MyBase::operator*());
		}

		ReferenceType operator[](size_t index)
		{
			return const_cast<ReferenceType>(MyBase::operator[](index));
		}

		PointerType operator->() noexcept
		{
			return const_cast<PointerType>(MyBase::operator->());
		}

		ListReversedIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		ListReversedIterator operator++(int)
		{
			ListIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		ListReversedIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		ListReversedIterator operator--(int)
		{
			ListIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		ListReversedIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		ListReversedIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		ListReversedIterator operator+(size_t right)
		{
			return ListReversedIterator(MyBase::operator+(right).GetElement());
		}

		ListReversedIterator operator-(size_t right)
		{
			return ListReversedIterator(MyBase::operator-(right).GetElement());
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const ListReversedIterator& right)
		{
			return MyBase::operator-(right);
		}

		ListReversedIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}
	};

	template <typename T>
	class List
	{
	public: 
		using DataType = T;

		using Element = ListElement<T>;

		using ConstIterator = ListConstIterator<List<DataType>>;
		using Iterator = ListIterator<List<DataType>>;

		using ConstReversedIterator = ListConstReversedIterator<List<DataType>>;
		using ReversedIterator = ListReversedIterator<List<DataType>>;

	private:
		Element* m_Front = nullptr;
		Element* m_Back = nullptr;

		Element* m_LeftEnd;
		Element* m_RightEnd;

		size_t m_Size = 0;

	private:
		void PutNextToEachOther(Element* left, Element* right)
		{
			left->next = right;
			right->prev = left;
		}

	public:
		List()
		{
			m_LeftEnd = new Element();
			m_RightEnd = new Element();
			PutNextToEachOther(m_LeftEnd, m_RightEnd);
		}

		List(const List& other)
		{
			m_LeftEnd = new Element();
			m_RightEnd = new Element();
			PutNextToEachOther(m_LeftEnd, m_RightEnd);

			for (auto& it : other)
				PushBack(it);
		}

		List(std::initializer_list<DataType> list)
		{
			m_LeftEnd = new Element();
			m_RightEnd = new Element();
			PutNextToEachOther(m_LeftEnd, m_RightEnd);

			for (auto& it : list)
				PushBack(std::move(it));
		}

		List(List&& other) noexcept
		{
			m_LeftEnd = new Element();
			m_RightEnd = new Element();
			PutNextToEachOther(m_LeftEnd, m_RightEnd);

			m_Size = other.m_Size;
			m_Front = other.m_Front;
			m_Back = other.m_Back;

			if (m_Size > 0)
			{
				PutNextToEachOther(m_LeftEnd, m_Front);
				PutNextToEachOther(m_Back, m_RightEnd);
			}

			PutNextToEachOther(other.m_LeftEnd, other.m_RightEnd);
			other.m_Size = 0;
			other.m_Front = nullptr;
			other.m_Back = nullptr;
		}

		~List()
		{
			Clear();

			delete m_RightEnd;
			delete m_LeftEnd;
		}

		void Assign(const DataType& value, size_t count = 1)
		{
			if (count == m_Size)
			{
				for (Iterator it = begin();
					it != end(); it++)
				{
					*it = value;
				}
			}
			else
			{
				Clear();
				for (size_t i = 0; i < count; i++)
					PushBack(value);
			}
		}

		void Assign(std::initializer_list<DataType> list)
		{
			if (m_Size == list.size())
			{
				auto otherIt = list.begin();
				for (Iterator it = begin();
					it != end(); it++, otherIt++)
				{
					*it = *otherIt;
				}
			}
			else
			{
				Clear();
				for (auto& it : list)
					PushBack(std::move(it));
			}
		}

		void PushBack(const DataType& data)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(data, m_LeftEnd, m_RightEnd);
				m_Front = m_Back;
			}
			else
			{
				Element* oldBack = m_Back;
				m_Back = new Element(data);

				oldBack->next = m_Back;
			}

			m_Size++;
		}
		
		void PushBack(DataType&& data)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(std::move(data), m_LeftEnd, m_RightEnd);
				m_Front = m_Back;
			}
			else
			{
				Element* oldBack = m_Back;
				m_Back = new Element(std::move(data), oldBack, m_RightEnd);

				oldBack->next = m_Back;
			}

			m_Size++;
		}

		template <typename ...Args>
		DataType& EmplaceBack(Args&&... args)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(m_LeftEnd, m_RightEnd, args...);
				m_Front = m_Back;
			}
			else
			{
				Element* oldBack = m_Back;
				m_Back = new Element(oldBack, m_RightEnd, args...);

				oldBack->next = m_Back;
			}

			m_Size++;

			return m_Back->data;
		}

		void PushFront(const DataType& data)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(data, m_LeftEnd, m_RightEnd);
				m_Front = m_Back;
			}
			else
			{
				Element* oldFront = m_Front;
				m_Front = new Element(data, m_LeftEnd, oldFront);

				oldFront->prev = m_Front;
			}

			m_Size++;
		}

		void PushFront(DataType&& data)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(std::move(data), m_LeftEnd, m_RightEnd);
				m_Front = m_Back;
			}
			else
			{
				Element* oldFront = m_Front;
				m_Front = new Element(std::move(data), m_LeftEnd, oldFront);

				oldFront->prev = m_Front;
			}

			m_Size++;
		}

		template <typename ...Args>
		DataType& EmplaceFront(Args&&... args)
		{
			if (m_Size == 0)
			{
				m_Back = new Element(m_LeftEnd, m_RightEnd, args...);
				m_Front = m_Back;
			}
			else
			{
				Element* oldFront = m_Front;
				m_Front = new Element(m_LeftEnd, oldFront, args...);

				oldFront->prev = m_Front;
			}

			m_Size++;

			return m_Back->data;
		}

		void PopBack()
		{
			if (m_Size == 1)
			{
				delete m_Back;

				PutNextToEachOther(m_LeftEnd, m_RightEnd);

				m_Back = nullptr;
				m_Front = nullptr;
			}
			else
			{
				Element* elementToDelete = m_Back;
				m_Back = m_Back->prev;

				delete elementToDelete;

				PutNextToEachOther(m_Back, m_RightEnd);
			}

			m_Size--;
		}

		void PopFront()
		{
			if (m_Size == 1)
			{
				delete m_Front;

				PutNextToEachOther(m_LeftEnd, m_RightEnd);

				m_Back = nullptr;
				m_Front = nullptr;
			}
			else
			{
				Element* elementToDelete = m_Front;
				m_Front = m_Front->next;

				delete elementToDelete;

				PutNextToEachOther(m_LeftEnd, m_Front);
			}

			m_Size--;
		}

		void Clear()
		{
			if (m_Size == 0)
				return;

			ConstIterator it(m_Front);
			const Element* elementToDelete = nullptr;

			while (it != end())
			{
				elementToDelete = it.GetElement();
				it++;
				delete elementToDelete;
			}

			PutNextToEachOther(m_LeftEnd, m_RightEnd);
			m_Size = 0;
		}

		void Insert(ConstIterator where, const DataType& value, int count = 1)
		{
			Element* whereElement = const_cast<Element*>(where.GetElement());

			for (size_t i = 0; i < count; i++)
				Element* newElement = new Element(value, whereElement->prev, whereElement);
			
			m_Size += count;

			m_Front = m_LeftEnd->next;
			m_Back = m_RightEnd->prev;
		}

		template <typename ...Args>
		Iterator Emplace(ConstIterator where, Args&&... args)
		{
			Element* whereElement = const_cast<Element*>(where.GetElement());

			Element* newElement = new Element(whereElement->prev, whereElement, args...);

			m_Size++;

			m_Front = m_LeftEnd->next;
			m_Back = m_RightEnd->prev;

			return Iterator(newElement);
		}

		void Erase(ConstIterator where)
		{
			Element* elementToDelete = const_cast<Element*>(where.GetElement());
			PutNextToEachOther(elementToDelete->prev, elementToDelete->next);

			delete elementToDelete;

			m_Size--;
			if (IsEmpty())
			{
				m_Front = nullptr;
				m_Back = nullptr;
			}
			else
			{
				m_Front = m_LeftEnd->next;
				m_Back = m_RightEnd->prev;
			}
		}

		// first inclusive and last exclusive
		void Erase(ConstIterator first, ConstIterator last)
		{
			ConstIterator leftIt = first - 1;
			PutNextToEachOther(
				const_cast<Element*>(leftIt.GetElement()), 
				const_cast<Element*>(last.GetElement()));

			ConstIterator it(first);
			const Element* elementToDelete = nullptr;

			while (it != last)
			{
				elementToDelete = it.GetElement();
				it++;
				delete elementToDelete;
				m_Size--;
			}

			if (IsEmpty())
			{
				m_Front = nullptr;
				m_Back = nullptr;
			}
			else
			{
				m_Front = m_LeftEnd->next;
				m_Back = m_RightEnd->prev;
			}
		}

		void Swap(List& other)
		{
			List temp = std::move(other);
			other = std::move(*this);
			*this = std::move(temp);
		}

		void Resize(size_t newSize)
		{
			if (newSize > m_Size)
			{
				size_t count = newSize - m_Size;
				for (size_t i = 0; i < count; i++)
					EmplaceBack();
			}
			else if (newSize < m_Size)
			{
				size_t count = m_Size - newSize;
				for (size_t i = 0; i < count; i++)
					PopBack();
			}
		}

		void Remove(const DataType& value)
		{
			Iterator it(m_Front);
			Element* elementToDelete = nullptr;

			while (it != end())
			{
				if (*it == value)
				{
					elementToDelete = it.GetElement();
					it++;

					PutNextToEachOther(elementToDelete->prev, elementToDelete->next);

					delete elementToDelete;
					m_Size--;
				}
				else
				{
					it++;
				}
			}
			if (IsEmpty())
			{
				m_Front = nullptr;
				m_Back = nullptr;
			}
			else
			{
				m_Front = m_LeftEnd->next;
				m_Back = m_RightEnd->prev;
			}
		}

		List& operator=(const List& other)
		{
			if (*this != other)
			{
				if (m_Size == other.m_Size)
				{
					ConstIterator otherIt = other.begin();

					for (Iterator it = begin();
						it != end(); it++, otherIt++)
					{
						*it = *otherIt;
					}
				}
				else
				{
					Clear();
					for (auto& it : other)
						PushBack(it);
				}
			}
			return *this;
		}
		
		List& operator=(List&& other) noexcept
		{
			if (*this != other)
			{
				Clear();
				m_Size = other.m_Size;
				m_Front = other.m_Front;
				m_Back = other.m_Back;

				if (m_Size > 0)
				{
					PutNextToEachOther(m_LeftEnd, m_Front);
					PutNextToEachOther(m_Back, m_RightEnd);
				}

				PutNextToEachOther(other.m_LeftEnd, other.m_RightEnd);
				other.m_Size = 0;
				other.m_Front = nullptr;
				other.m_Back = nullptr;
			}
			return *this;
		}

		bool operator==(const List& other)
		{
			if (m_Size != other.m_Size)
				return false;

			ConstIterator otherIt = other.begin();
			for (Iterator it = begin();
				it != end(); it++, otherIt++)
			{
				if (*it != *otherIt)
					return false;
			}

			return true;
		}

		bool operator!=(const List& other)
		{
			return !(*this == other);
		}

		/* GETTERS & SETTERS */

		DataType& Front() { return m_Front->data; }
		const DataType& Front() const { return m_Front->data; }

		DataType& Back() { return m_Back->data; }
		const DataType& Back() const { return m_Back->data; }

		DataType& operator[](size_t index) { return *(begin() + index); }
		const DataType& operator[](size_t index) const { return *(begin() + index); }

		size_t Size() const { return m_Size; }

		bool IsEmpty() const { return m_Size == 0; }

		// default iterators
		Iterator begin() 
		{ 
			if (IsEmpty())
				return end();
			return Iterator(m_Front); 
		}
		ConstIterator begin() const 
		{ 
			if (IsEmpty())
				return end();
			return ConstIterator(m_Front); 
		}

		Iterator end() { return Iterator(m_RightEnd); }
		ConstIterator end() const { return ConstIterator(m_RightEnd); }

		// reversed iterators
		ReversedIterator rbegin()
		{ 
			if (IsEmpty())
				return rend();
			return ReversedIterator(m_Back); 
		}
		ConstReversedIterator rbegin() const 
		{ 
			if (IsEmpty())
				return rend();
			return ConstReversedIterator(m_Back); 
		}

		ReversedIterator rend() { return ReversedIterator(m_LeftEnd); }
		ConstReversedIterator rend() const { return ConstReversedIterator(m_LeftEnd); }

		// const iterators
		ConstIterator cbegin() const
		{
			if (IsEmpty())
				return end();
			return ConstIterator(m_Front);
		}
		ConstIterator cend() const { return ConstIterator(m_RightEnd); }

		ConstReversedIterator crbegin() const
		{
			if (IsEmpty())
				return rend();
			return ConstReversedIterator(m_Back);
		}
		ConstReversedIterator crend() const { return ConstReversedIterator(m_LeftEnd); }
	};
}