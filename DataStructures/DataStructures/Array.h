#pragma once
namespace DataStructures
{
	template <typename MyArray>
	class ArrayConstIterator
	{
	public:
		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;
		using PointerType = DataType*;
		using ConstPointerType = const DataType*;

	private:
		ConstPointerType m_Ptr;

	public:
		ArrayConstIterator() noexcept
			: m_Ptr(nullptr)
		{
		}

		explicit ArrayConstIterator(ConstPointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		ArrayConstIterator(const ArrayConstIterator& other) noexcept
			: m_Ptr(other.m_Ptr)
		{
		}

		ConstPointerType operator->() const
		{
			return m_Ptr;
		}

		ConstReferenceType operator*() const
		{
			return *(m_Ptr);
		}

		ConstReferenceType operator[](size_t index) 
		{
			return *(m_Ptr + index);
		}

		ArrayConstIterator operator++() 
		{
			m_Ptr++;
			return *this;
		}

		ArrayConstIterator operator++(int)
		{
			ArrayConstIterator temp = *this;
			m_Ptr++;
			return temp;
		}

		ArrayConstIterator operator--() 
		{
			m_Ptr--;
			return *this;
		}

		ArrayConstIterator operator--(int) 
		{
			ArrayConstIterator temp = *this;
			m_Ptr--;
			return temp;
		}

		ArrayConstIterator operator+=(size_t right)
		{
			m_Ptr += right;
			return *this;
		}

		ArrayConstIterator operator-=(size_t right)
		{
			m_Ptr -= right;
			return *this;
		}

		ArrayConstIterator operator+(size_t right) 
		{
			ArrayConstIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr + right;
			return temp;
		}

		ArrayConstIterator operator-(size_t right)
		{
			ArrayConstIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr - right;
			return temp;
		}

		size_t operator-(const ArrayConstIterator& right) 
		{
			return m_Ptr - right.m_Ptr;
		}

		ArrayConstIterator& operator=(const ArrayConstIterator& other)
		{
			if (m_Ptr != other.m_Ptr)
			{
				m_Ptr = other.m_Ptr;
			}
			return *this;
		}

		ArrayConstIterator& operator=(ConstPointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		ArrayConstIterator& operator=(PointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const ArrayConstIterator& other) 
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ArrayConstIterator& other) 
		{
			return !(m_Ptr == other.m_Ptr);
		}
	};

	template <typename MyArray>
	class ArrayIterator : public ArrayConstIterator<MyArray>
	{
	public:
		using MyBase = ArrayConstIterator<MyArray>;

		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using PointerType = DataType*;

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

		PointerType operator->()
		{
			return const_cast<ReferenceType>(MyBase::operator->());
		}

		ArrayIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		ArrayIterator operator++(int)
		{
			ArrayIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		ArrayIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		ArrayIterator operator--(int)
		{
			ArrayIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		ArrayIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		ArrayIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		ArrayIterator operator+(size_t right)
		{
			MyBase::operator+(right);
			return *this;
		}

		ArrayIterator operator-(size_t right)
		{
			MyBase::operator-(right);
			return *this;
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const ArrayIterator& right)
		{
			return MyBase::operator-(right);
		}

		ArrayIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}
	};

	template <typename MyArray>
	class ArrayConstReversedIterator
	{
	public:
		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;
		using PointerType = DataType*;
		using ConstPointerType = const DataType*;

	private:
		ConstPointerType m_Ptr;

	public:
		ArrayConstReversedIterator() noexcept
			: m_Ptr(nullptr)
		{
		}

		explicit ArrayConstReversedIterator(ConstPointerType ptr) noexcept
			: m_Ptr(ptr)
		{
		}

		ArrayConstReversedIterator(const ArrayConstReversedIterator& other) noexcept
			: m_Ptr(other.m_Ptr)
		{
		}

		ConstPointerType operator->() const
		{
			return m_Ptr;
		}

		ConstReferenceType operator*() const
		{
			return *(m_Ptr);
		}

		ConstReferenceType operator[](size_t index)
		{
			return *(m_Ptr + index);
		}

		ArrayConstReversedIterator operator++()
		{
			m_Ptr--;
			return *this;
		}

		ArrayConstReversedIterator operator++(int)
		{
			ArrayConstReversedIterator temp = *this;
			m_Ptr--;
			return temp;
		}

		ArrayConstReversedIterator operator--()
		{
			m_Ptr++;
			return *this;
		}

		ArrayConstReversedIterator operator--(int)
		{
			ArrayConstReversedIterator temp = *this;
			m_Ptr++;
			return temp;
		}

		ArrayConstReversedIterator operator+=(size_t right)
		{
			m_Ptr -= right;
			return *this;
		}

		ArrayConstReversedIterator operator-=(size_t right)
		{
			m_Ptr += right;
			return *this;
		}

		ArrayConstReversedIterator operator+(size_t right)
		{
			ArrayConstReversedIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr - right;
			return temp;
		}

		ArrayConstReversedIterator operator-(size_t right)
		{
			ArrayConstReversedIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr + right;
			return temp;
		}

		size_t operator-(const ArrayConstReversedIterator& right)
		{
			return m_Ptr - right.m_Ptr;
		}

		ArrayConstReversedIterator& operator=(const ArrayConstReversedIterator& other)
		{
			if (m_Ptr != other.m_Ptr)
			{
				m_Ptr = other.m_Ptr;
			}
			return *this;
		}

		ArrayConstReversedIterator& operator=(ConstPointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		ArrayConstReversedIterator& operator=(PointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const ArrayConstReversedIterator& other)
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ArrayConstReversedIterator& other)
		{
			return !(m_Ptr == other.m_Ptr);
		}
	};

	template <typename MyArray>
	class ArrayReversedIterator : public ArrayConstReversedIterator<MyArray>
	{
	public:
		using MyBase = ArrayConstReversedIterator<MyArray>;

		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using PointerType = DataType*;

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

		PointerType operator->()
		{
			return const_cast<ReferenceType>(MyBase::operator->());
		}

		ArrayReversedIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		ArrayReversedIterator operator++(int)
		{
			ArrayReversedIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		ArrayReversedIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		ArrayReversedIterator operator--(int)
		{
			ArrayReversedIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		ArrayReversedIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		ArrayReversedIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		ArrayReversedIterator operator+(size_t right)
		{
			MyBase::operator+(right);
			return *this;
		}

		ArrayReversedIterator operator-(size_t right)
		{
			MyBase::operator-(right);
			return *this;
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const ArrayReversedIterator& right)
		{
			return MyBase::operator-(right);
		}

		ArrayReversedIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}
	};

	template <typename T, size_t _Size>
	class Array
	{
	public:
		using DataType = T;

		using ConstIterator = ArrayConstIterator<Array<DataType, _Size>>;
		using Iterator = ArrayIterator<Array<DataType, _Size>>;

		using ConstReversedIterator = ArrayConstReversedIterator<Array<DataType, _Size>>;
		using ReversedIterator = ArrayReversedIterator<Array<DataType, _Size>>;

	private:
		DataType m_Data[_Size];

	public:
		/* Constructors & Destructors */

		Array()
		{
		}

		Array(const Array& other)
		{
			for (size_t i = 0; i < _Size; i++)
				m_Data[i] = other.m_Data[i];
		}

		Array(std::initializer_list<DataType> list)
		{
			int i = 0;
			for (auto& it : list)
			{
				m_Data[i] = it;
				i++;
			}
		}

		~Array()
		{
		}

		/* Functionality */

		void Fill(const DataType& value)
		{
			for (size_t i = 0; i < _Size; i++)
				m_Data[i] = value;
		}
		
		void Swap(const Array& other)
		{
			Array temp = other;
			other = *this;
			*this = temp;
		}

		/* Operators */

		Array& operator=(const Array& other)
		{
			if (*this != other)
			{
				for (size_t i = 0; i < _Size; i++)
					m_Data[i] = other.m_Data[i];
			}
			return *this;
		}

		/* Getters & Setters */

		// getter/setter - getter available when array is const (second line)
		DataType& Front() { return m_Data[0]; }
		const DataType& Front() const { return m_Data[0]; }

		// getter/setter - getter available when array is const (second line)
		DataType& Back() { return m_Data[_Size - 1]; }
		const DataType& Back() const { return m_Data[_Size - 1]; }

		// getter/setter - getter available when array is const (second line)
		DataType& operator[](size_t index) { return m_Data[index]; }
		const DataType& operator[](size_t index) const { return m_Data[index]; }

		// getter/setter - getter available when array is const (second line)
		DataType* Data() { return m_Data; }
		const DataType* Data() const { return m_Data; }

		// getter (available when array is const)
		size_t Size() const { return _Size; }

		// getter (available when array is const)
		bool IsEmpty() const { return _Size == 0; }

		// default iterators
		Iterator begin() { return Iterator(m_Data); }
		ConstIterator begin() const { return ConstIterator(m_Data); }

		Iterator end() { return Iterator(m_Data + _Size); }
		ConstIterator end() const { return ConstIterator(m_Data + _Size); }

		// reversed iterators
		ReversedIterator rbegin() { return ReversedIterator(m_Data + _Size - 1); }
		ConstReversedIterator rbegin() const { return ConstReversedIterator(m_Data + _Size - 1); }

		ReversedIterator rend() { return ReversedIterator(m_Data - 1); }
		ConstReversedIterator rend() const { return ConstReversedIterator(m_Data - 1); }

		// const iterators
		ConstIterator cbegin() const { return ConstIterator(m_Data); }
		ConstIterator cend() const { return ConstIterator(m_Data + _Size); }
		ConstReversedIterator crbegin() const { return ConstReversedIterator(m_Data + _Size - 1); }
		ConstReversedIterator crend() const { return ConstReversedIterator(m_Data - 1); }
	};
}