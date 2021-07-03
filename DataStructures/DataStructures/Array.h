#pragma once

namespace DataStructures
{
	template <typename MyArray>
	class ConstArrayIterator
	{
	public:
		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const ReferenceType;
		using PointerType = DataType*;
		using ConstPointerType = const PointerType const;

	protected:
		PointerType m_Ptr;

	public:
		ConstArrayIterator(PointerType ptr)
			: m_Ptr(ptr)
		{
		}

		ConstArrayIterator(const ConstArrayIterator& other)
			: m_Ptr(other.m_Ptr)
		{

		}

		ConstReferenceType operator*() const
		{
			return *m_Ptr;
		}

		ConstReferenceType operator[](size_t index) const
		{
			return m_Ptr + index;
		}

		ConstPointerType operator->() const
		{
			return m_Ptr;
		}

		ConstArrayIterator operator++() const
		{
			m_Ptr++;
			return *this;
		}

		ConstArrayIterator operator++(int) const
		{
			ConstArrayIterator temp = *this;
			m_Ptr++;
			return temp;
		}

		ConstArrayIterator operator--() const
		{
			m_Ptr--;
			return *this;
		}

		ConstArrayIterator operator--(int) const
		{
			ConstArrayIterator temp = *this;
			m_Ptr--;
			return temp;
		}

		ConstArrayIterator operator+(int right) const
		{
			ConstArrayIterator temp = left;
			temp.m_Ptr = temp.m_Ptr + right;
			return temp;
		}

		size_t operator-(const ConstArrayIterator& right) const
		{
			return left.m_Ptr - right.m_Ptr;
		}

		ConstArrayIterator operator-(int right) const
		{
			ConstArrayIterator temp = left;
			temp.m_Ptr = temp.m_Ptr - right;
			return temp;
		}

		bool operator==(const ConstArrayIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const ConstArrayIterator& other) const
		{
			return !(m_Ptr == other.m_Ptr);
		}

	};

	template <typename MyArray>
	class ArrayIterator : public ConstVectorIterator<MyArray>
	{
	public:
		using DataType = typename MyArray::DataType;
		using ReferenceType = DataType&;
		using PointerType = DataType*;

	public:
		ReferenceType operator*()
		{
			return *m_Ptr;
		}

		ReferenceType operator[](size_t index)
		{
			return m_Ptr + index;
		}

		PointerType operator->()
		{
			return m_Ptr;
		}

		ArrayIterator& operator=(const ConstArrayIterator& it)
		{
			if (*this != it)
			{
				m_Ptr = it.m_Ptr;
			}
			return *this;
		}

		ArrayIterator operator=(PointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
			}
			return *this;
		}
	};

	template <typename T, size_t _Size>
	class Array
	{
	public:
		using DataType = T;

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
	};
}