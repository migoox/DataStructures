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
		size_t m_IdOffset;

	public:
		ArrayConstIterator() noexcept
			: m_Ptr(nullptr), m_IdOffset(0)
		{
		}

		explicit ArrayConstIterator(ConstPointerType ptr, size_t id_off = 0) noexcept
			: m_Ptr(ptr), m_IdOffset(id_off)
		{
		}

		ArrayConstIterator(const ArrayConstIterator& other) noexcept
			: m_Ptr(other.m_Ptr), m_IdOffset(other.m_IdOffset)
		{
		}

		ConstPointerType operator->() const
		{
			return m_Ptr + m_IdOffset;
		}

		ConstReferenceType operator*() const
		{
			return *(m_Ptr + m_IdOffset);
		}

		ConstReferenceType operator[](size_t index) 
		{
			return *(m_Ptr + m_IdOffset + index);
		}

		ArrayConstIterator operator++() 
		{
			m_IdOffset++;
			return *this;
		}

		ArrayConstIterator operator++(int)
		{
			ArrayConstIterator temp = *this;
			m_IdOffset++;
			return temp;
		}

		ArrayConstIterator operator--() 
		{
			m_IdOffset--;
			return *this;
		}

		ArrayConstIterator operator--(int) 
		{
			ArrayConstIterator temp = *this;
			m_IdOffset--;
			return temp;
		}
		ArrayConstIterator operator+(int right) 
		{
			ArrayConstIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr + right;
			return temp;
		}

		size_t operator-(const ArrayConstIterator& right) 
		{
			return m_Ptr - right.m_Ptr;
		}

		ArrayConstIterator operator-(int right) 
		{
			ArrayConstIterator temp = *this;
			temp.m_Ptr = temp.m_Ptr - right;
			return temp;
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
			return const_cast<ReferenceType>(MyBase::operator[]());
		}

		PointerType operator->()
		{
			return const_cast<ReferenceType>(MyBase::operator->());
		}
	};

	template <typename T, size_t _Size>
	class Array
	{
	public:
		using DataType = T;

		using ConstIterator = ArrayConstIterator<Array<DataType, _Size>>;
		using Iterator = ArrayIterator<Array<DataType, _Size>>;

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

		// getter/setter - getter available when vector is const (second line)
		DataType& Front() { return m_Data[0]; }
		const DataType& Front() const { return m_Data[0]; }

		// getter/setter - getter available when vector is const (second line)
		DataType& Back() { return m_Data[_Size - 1]; }
		const DataType& Back() const { return m_Data[_Size - 1]; }

		// getter/setter - getter available when vector is const (second line)
		DataType& operator[](size_t index) { return m_Data[index]; }
		const DataType& operator[](size_t index) const { return m_Data[index]; }

		// getter/setter - getter available when vector is const (second line)
		DataType* Data() { return m_Data; }
		const DataType* Data() const { return m_Data; }

		// getter (available when vector is const)
		size_t Size() const { return _Size; }

		// getter (available when vector is const)
		bool IsEmpty() const { return _Size == 0; }

		Iterator begin() { return Iterator(m_Data, 0); }
		ConstIterator begin() const { return ConstIterator(m_Data, 0); }

		Iterator end() { return Iterator(m_Data, _Size); }
		ConstIterator end() const { return ConstIterator(m_Data, _Size); }
	};
}