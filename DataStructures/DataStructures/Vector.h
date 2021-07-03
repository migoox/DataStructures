#pragma once

namespace DataStructures
{
	template <typename MyVector>
	class VectorIterator
	{
	public:
		using ValueType = typename MyVector::ValueType;
		using PointerType = ValueType*;
		using ReferenceType = ValueType&;

	private:
		PointerType m_Ptr;

	public:
		VectorIterator(PointerType ptr)
			: m_Ptr(ptr)
		{ 
		
		}

		VectorIterator(const VectorIterator& it)
			: m_Ptr(it.m_Ptr)
		{

		}
		
		ReferenceType operator*() 
		{ 
			return *m_Ptr; 
		}

		ReferenceType operator[](int index) 
		{ 
			return *(m_Ptr + index); 
		}

		ReferenceType operator=(const VectorIterator& it)
		{
			if (*this != it)
			{
				m_Ptr = it.m_Ptr;
			}
			return *this;
		}

		VectorIterator operator++() 
		{ 
			++m_Ptr;
			return *this; 
		}

		VectorIterator operator++(int) 
		{ 
			VectorIterator temp = *this;
			++m_Ptr;
			return temp;
		}

		VectorIterator operator--()
		{
			--m_Ptr;
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator temp = *this;
			--m_Ptr;
			return temp;
		}

		PointerType operator->() 
		{ 
			return m_Ptr; 
		}

		friend VectorIterator operator+(const VectorIterator& left, int right)
		{
			VectorIterator temp = left;
			temp.m_Ptr = temp.m_Ptr + right;
			return temp;
		}

		friend VectorIterator operator-(const VectorIterator& left, int right)
		{
			VectorIterator temp = left;
			temp.m_Ptr = temp.m_Ptr - right;
			return temp;
		}

		bool operator==(const VectorIterator& other) const
		{
			return m_Ptr == other.m_Ptr;
		}

		bool operator!=(const VectorIterator& other) const
		{
			return !(m_Ptr == other.m_Ptr);
		}
	};

	template <typename T>
	class Vector
	{
	public:
		using ValueType = T;
		using Iterator = typename VectorIterator<Vector<ValueType>>;
	private:
		size_t m_sSize = 0;
		size_t m_sCapacity = 0;

		ValueType* m_tData = nullptr;
	private:

		void ReAlloc(size_t newCapacity)
		{
			// call destructors in this case
			if (m_sSize > newCapacity)
			{
				int length = m_sSize - newCapacity;
				for (size_t i = 0; i < length; i++)
					PopBack();
			}

			// allocating memory without calling constructor
			ValueType* newBlock = (ValueType*)::operator new(newCapacity * sizeof(T));

			// calling move constractor for each element of newBlock
			// if move is not defined, simple copy will be called
			for (size_t i = 0; i < m_sSize; i++)
				new (&newBlock[i]) ValueType(std::move(m_tData[i]));

			// destructing all of the elements from previous scope of memory
			for (size_t i = 0; i < m_sSize; i++)
				m_tData[i].~T();
			
			// dealocating old scope of memory
			::operator delete(m_tData, m_sCapacity * sizeof(ValueType));

			// saving new capacity
			m_sCapacity = newCapacity;

			// pointing to know block of data
			m_tData = newBlock;
		}

	public:

		/* Constructor & Destructor */
		
		// default constructor
		Vector()
		{
			// allocating scope of 2 elements
			ReAlloc(2);
		}

		// copy constructor
		Vector(const Vector& other) // copy constructor
		{
			// allocating enough memory to copy all of the data (capacity is described)
			ReAlloc(other.m_sSize);

			// saving size
			m_sSize = other.m_sSize;

			// copying
			for (size_t i = 0; i < m_sSize; i++)
				new (&m_tData[i]) ValueType(other.m_tData[i]);
		}

		// move constructor
		Vector(Vector&& other) noexcept  // move constructor
		{
			// allocating enough memory to move all of the data (capacity is described)
			ReAlloc(other.m_sSize);

			// saving size
			m_sSize = other.m_sSize;

			// moving
			for (size_t i = 0; i < m_sSize; i++)
				new (&m_tData[i]) ValueType(std::move(other.m_tData[i]));
		}

		// destructor
		~Vector()
		{
			// calling destructors of all the data included
			Clear(); 
			
			// dealocating memory
			::operator delete(m_tData, m_sCapacity * sizeof(T));
		}

		/* Functionality */

		void Clear()
		{
			// calling destructors but without dealocating, capacity stays the same
			for (size_t i = 0; i < m_sSize; i++)
				m_tData[i].~ValueType();

			m_sSize = 0;
		}

		void ShrinkToFit()
		{
			ReAlloc(m_sSize);	
		}

		void Resize(size_t size)
		{
			if (size == m_sSize)
			{
				return;
			}
			else if(size > m_sCapacity)
			{
				ReAlloc(size);
			}
			for (size_t i = m_sSize; i < size; i++)
				new (&m_tData[i]) ValueType();

			m_sSize = size;
		}

		void Reserve(size_t newCapacity)
		{
			ReAlloc(newCapacity);
		}

		void PushBack(const ValueType& element)
		{
			if (m_sSize + 1 >= m_sCapacity)
			{
				ReAlloc(m_sSize + m_sSize / 2);
			}

			// use a copy constructor of ValueType and copy element
			new (&m_tData[m_sSize]) ValueType(element);

			m_sSize++;
		}

		void PushBack(ValueType&& element)
		{
			// if there is lack of place in current scope allocate a new wider one 
			if (m_sSize + 1 > m_sCapacity)
				ReAlloc(m_sSize + m_sSize / 2);

			// use a move constructor of ValueType and copy element
			new (&m_tData[m_sSize]) ValueType(std::move(element));

			m_sSize++;
		}

		template <typename ...Args>
		ValueType& EmplaceBack(Args&&... args)
		{
			// if there is lack of place in current scope allocate a new wider one 
			if (m_sSize + 1 > m_sCapacity)
				ReAlloc(m_sSize + m_sSize / 2);

			// put forward given arguments to constructor of ValueType 
			new(&m_tData[m_sSize]) ValueType(std::forward<Args>(args)...);
			return m_tData[m_sSize++];
		}

		void PopBack()
		{
			m_tData[--m_sSize].~T();
		}

		void Swap(Vector<ValueType>& other)
		{
			Vector<ValueType> temp = std::move(other);
			other = std::move(*this);
			*this = std::move(temp);
		}

		void Erase(Iterator where)
		{
			// deleting element
			where->~ValueType();

			// moving elements to make vector contiguous
			Iterator current = where;
			for (Iterator it = where + 1; it != end(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_sSize--;
		}

		// first inclusive and last exclusive
		void Erase(Iterator first, Iterator last)
		{
			size_t count = 0;
			// deleting elements
			for (Iterator it = first; it != last; it++)
			{
				it->~ValueType();
				count++;
			}
			
			// moving elements to make vector contiguous
			Iterator current = first;
			for (Iterator it = last; it != end(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_sSize -= count;
		}
		
		void Insert(Iterator where, const ValueType& var)
		{
			if (m_sSize + 1 >= m_sCapacity)
			{
				ReAlloc(m_sSize + m_sSize / 2);
			}

			new (&m_tData[m_sSize]) ValueType();

			for (Iterator bottomIt = end() - 1, topIt = end(); 
				bottomIt != begin() - 1; 
				bottomIt--, topIt--)
			{
				*topIt = std::move(*bottomIt);
			}

			begin()->~ValueType();

			new (&m_tData[0]) ValueType(var);

			m_sSize++;
		}

		void Insert(Iterator where, int count, const ValueType& var)
		{
			if (m_sSize + 1 >= m_sCapacity)
			{
				if (m_sSize + m_sSize / 2 < count)
					ReAlloc(m_sSize + count);
				else
					ReAlloc(m_sSize + m_sSize / 2);
			}

			for (size_t i = 0; i < count; i++)
				new (&m_tData[m_sSize + i]) ValueType();

			for (Iterator bottomIt = end() - 1, topIt = end() + count;
				bottomIt != begin() - 1;
				bottomIt--, topIt--)
			{
				*topIt = std::move(*bottomIt);
			}

			for (size_t i = 0; i < count; i++)
				(begin() + i)->~ValueType();

			for (size_t i = 0; i < count; i++)
			{
				new (&m_tData[i]) ValueType(var);
				m_sSize++;
			}

		}

		/* Operators */

		// copy assignment
		Vector& operator=(const Vector& other)
		{
			if (*this != other)
			{
				if (m_sSize != other.m_sSize)
					ReAlloc(other.m_sSize);

				for (size_t i = 0; i < m_sSize; i++)
				{
					m_tData[i].~ValueType();
				}

				m_sSize = other.m_sSize;

				for (size_t i = 0; i < m_sSize; i++)
				{
					new (&m_tData[i]) ValueType(other.m_tData[i]);
				}
			}
			return *this;
		}

		// move assignment
		Vector& operator=(Vector&& other) noexcept
		{
			if (*this != other)
			{
				if (m_sSize != other.m_sSize)
					ReAlloc(other.m_sSize);

				for (size_t i = 0; i < m_sSize; i++)
				{
					m_tData[i].~ValueType();
				}

				m_sSize = other.m_sSize;

				for (size_t i = 0; i < m_sSize; i++)
				{
					new (&m_tData[i]) ValueType(std::move(other.m_tData[i]));
				}
			}
			return *this;
		}

		bool operator==(const Vector& other)
		{
			if (m_sSize == other.m_sSize)
			{
				for (size_t i = 0; i < m_sSize; i++)
				{
					if (m_tData[i] != other.m_tData[i])
						return false;
				}
				return true;
			}
			return false;
		}

		bool operator!=(const Vector& other)
		{
			return !(*this == other);
		}

		/* Getters & Setters */

		// getter/setter - getter available when vector is const (second line)
		ValueType& Front() { return m_tData[0]; }
		const ValueType& Front() const { return m_tData[0]; }

		// getter/setter - getter available when vector is const (second line)
		ValueType& Back() { return m_tData[m_sSize - 1]; }
		const ValueType& Back() const { return m_tData[m_sSize - 1]; }

		// getter/setter - getter available when vector is const (second line)
		ValueType& operator[](int index) { return m_tData[index]; }
		const ValueType& operator[](int index) const { return m_tData[index]; } 

		int Size() const { return m_sSize; } // getter (available when vector is const)

		int Capacity() const { return m_sCapacity; } // getter (available when vector is const)

		bool IsEmpty() const { return m_sSize == 0; } // getter (available when vector is const)

		// foreach iterators
		Iterator begin() { return Iterator(m_tData); } // getting begin iterator (has to begin with small letter)

		Iterator end() { return Iterator(m_tData + m_sSize); } // getting end iterator (has to begin with small letter)

		// default iterators
		Iterator Begin() { return Iterator(m_tData); } // getting begin iterator (has to begin with small letter)

		Iterator End() { return Iterator(m_tData + m_sSize); } // getting end iterator (has to begin with small letter)
	};
}