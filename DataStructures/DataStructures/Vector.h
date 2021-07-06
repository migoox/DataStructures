#pragma once

namespace DataStructures
{
	template <typename MyVector>
	class ConstVectorIterator
	{
	public:
		using DataType = typename MyVector::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const ReferenceType;
		using PointerType = DataType*;
		using ConstPointerType = const PointerType;

	private:
		PointerType m_Ptr;

	public:
		ConstVectorIterator(PointerType ptr)
			: m_Ptr(ptr)
		{
		}

		ConstVectorIterator(const ConstVectorIterator& it)
			: m_Ptr(it.m_Ptr)
		{
		}

		ConstReferenceType operator*() const
		{
			return *m_Ptr;
		}

		ConstReferenceType operator[](size_t index) const
		{
			return *(m_Ptr + index);
		}

		ConstPointerType operator->() const
		{
			return m_Ptr;
		}
	};

	template <typename MyVector>
	class VectorIterator
	{
	public:
		using DataType = typename MyVector::DataType;
		using ReferenceType = DataType&;
		using PointerType = DataType*;

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

		PointerType operator->() const
		{
			return m_Ptr;
		}

		ReferenceType operator*() const
		{
			return *m_Ptr;
		}

		ReferenceType operator[](int index) const 
		{
			return *(m_Ptr + index);
		}

		VectorIterator& operator=(const VectorIterator& it)
		{
			if (*this != it)
			{
				m_Ptr = it.m_Ptr;
			}
			return *this;
		}

		VectorIterator operator=(PointerType ptr)
		{
			if (m_Ptr != ptr)
			{
				m_Ptr = ptr;
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

		friend size_t operator-(const VectorIterator& left, const VectorIterator& right)
		{
			return left.m_Ptr - right.m_Ptr;
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
		using DataType = T;
		using Iterator = typename VectorIterator<Vector<DataType>>;
		using ConstIterator = typename ConstVectorIterator<Vector<DataType>>;
	private:
		size_t m_Size = 0;
		size_t m_Capacity = 0;

		DataType* m_Data = nullptr;
	private:

		void ReAlloc(size_t newCapacity)
		{
			// call destructors in this case
			if (m_Size > newCapacity)
			{
				size_t length = m_Size - newCapacity;
				for (size_t i = 0; i < length; i++)
					PopBack();
			}

			// allocating memory without calling constructor
			DataType* newBlock = (DataType*)::operator new(newCapacity * sizeof(T));

			// calling move constractor for each element of newBlock
			// if move is not defined, simple copy will be called
			for (size_t i = 0; i < m_Size; i++)
				new (&newBlock[i]) DataType(std::move(m_Data[i]));

			// destructing all of the elements from previous scope of memory
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~T();
			
			// dealocating old scope of memory
			::operator delete(m_Data, m_Capacity * sizeof(DataType));

			// saving new capacity
			m_Capacity = newCapacity;

			// pointing to know block of data
			m_Data = newBlock;
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
			ReAlloc(other.m_Size);

			// saving size
			m_Size = other.m_Size;

			// copying
			for (size_t i = 0; i < m_Size; i++)
				new (&m_Data[i]) DataType(other.m_Data[i]);
		}

		// move constructor
		Vector(Vector&& other) noexcept  // move constructor
		{
			// allocating enough memory to move all of the data (capacity is described)
			ReAlloc(other.m_Size);

			// saving size
			m_Size = other.m_Size;

			// moving
			for (size_t i = 0; i < m_Size; i++)
				new (&m_Data[i]) DataType(std::move(other.m_Data[i]));
		}

		// destructor
		~Vector()
		{
			// calling destructors of all the data included
			Clear(); 
			
			// dealocating memory
			::operator delete(m_Data, m_Capacity * sizeof(T));
		}

		/* Functionality */

		void Clear()
		{
			// calling destructors but without dealocating, capacity stays the same
			for (size_t i = 0; i < m_Size; i++)
				m_Data[i].~DataType();

			m_Size = 0;
		}

		void ShrinkToFit()
		{
			ReAlloc(m_Size);	
		}

		void Resize(size_t size)
		{
			if (size == m_Size)
			{
				return;
			}
			else if(size > m_Capacity)
			{
				ReAlloc(size);
			}
			for (size_t i = m_Size; i < size; i++)
				new (&m_Data[i]) DataType();

			m_Size = size;
		}

		void Reserve(size_t newCapacity)
		{
			ReAlloc(newCapacity);
		}

		void PushBack(const DataType& element)
		{
			if (m_Size + 1 >= m_Capacity)
			{
				ReAlloc(m_Size + m_Size / 2);
			}

			// use a copy constructor of DataType and copy element
			new (&m_Data[m_Size]) DataType(element);

			m_Size++;
		}

		void PushBack(DataType&& element)
		{
			// if there is lack of place in current scope allocate a new wider one 
			if (m_Size + 1 > m_Capacity)
				ReAlloc(m_Size + m_Size / 2);

			// use a move constructor of DataType and copy element
			new (&m_Data[m_Size]) DataType(std::move(element));

			m_Size++;
		}

		template <typename ...Args>
		DataType& EmplaceBack(Args&&... args)
		{
			// if there is lack of place in current scope allocate a new wider one 
			if (m_Size + 1 > m_Capacity)
				ReAlloc(m_Size + m_Size / 2);

			// put forward given arguments to constructor of DataType 
			new(&m_Data[m_Size]) DataType(std::forward<Args>(args)...);
			return m_Data[m_Size++];
		}

		void PopBack()
		{
			m_Data[--m_Size].~T();
		}

		void Swap(Vector<DataType>& other)
		{
			Vector<DataType> temp = std::move(other);
			other = std::move(*this);
			*this = std::move(temp);
		}

		void Erase(Iterator where)
		{
			// deleting element
			where->~DataType();

			// moving elements to make vector contiguous
			Iterator current = where;
			for (Iterator it = where + 1; it != End(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_Size--;
		}

		// first inclusive and last exclusive
		void Erase(Iterator first, Iterator last)
		{
			size_t count = 0;
			// deleting elements
			for (Iterator it = first; it != last; it++)
			{
				it->~DataType();
				count++;
			}
			
			// moving elements to make vector contiguous
			Iterator current = first;
			for (Iterator it = last; it != End(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_Size -= count;
		}

		void EraseAt(size_t index)
		{
			Erase(Begin() + index);
		}

		void EraseAt(size_t index1, size_t index2)
		{
			Erase(Begin() + index1, Begin() + index2);
		}
		
		void Insert(Iterator where, const DataType& var, int count = 1)
		{
			// find index of where iterator
			// it's necessary, because after possible reallocation
			// adress of where will be different
			size_t whereIndex = where - Begin();

			// reallocate memory in case it's needed
			if (m_Size + count >= m_Capacity)
			{
				if (m_Size + m_Size / 2 < m_Size + count)
					ReAlloc(m_Size + count);
				else
					ReAlloc(m_Size + m_Size / 2);

				//reassign where pointer
				where = &m_Data[whereIndex];
			}

			// call default constructors at the new last elements
			for (size_t i = 0; i < count; i++)
				new (&m_Data[m_Size + i]) DataType();

			// move elements using move assignment
			for (Iterator bottomIt = End() - 1, topIt = End() + count - 1;
				bottomIt != where - 1;
				bottomIt--, topIt--)
			{
				*topIt = std::move(*bottomIt);
			}

			// finally assign new value to prepared place
			for (size_t i = 0; i < count; i++)
				new (&m_Data[whereIndex + i]) DataType(var);

			// increase the size by one
			m_Size += count;
		}

		void Insert(Iterator where, DataType&& var, int count = 1)
		{
			// find index of where iterator
			// it's necessary, because after possible reallocation
			// adress of where will be different
			size_t whereIndex = where - Begin();

			// reallocate memory in case it's needed
			if (m_Size + count >= m_Capacity)
			{
				if (m_Size + m_Size / 2 < m_Size + count)
					ReAlloc(m_Size + count);
				else
					ReAlloc(m_Size + m_Size / 2);

				//reassign where pointer
				where = &m_Data[whereIndex];
			}

			// call default constructors at the new last elements
			for (size_t i = 0; i < count; i++)
				new (&m_Data[m_Size + i]) DataType();

			// move elements using move assignment
			for (Iterator bottomIt = end() - 1, topIt = end() + count - 1;
				bottomIt != where - 1;
				bottomIt--, topIt--)
			{
				*topIt = std::move(*bottomIt);
			}

			// finally assign new value to prepared place
			for (size_t i = 0; i < count; i++)
				new (&m_Data[whereIndex + i]) DataType(std::move(var));

			// increase the size by one
			m_Size += count;
		}

		void InsertAt(size_t index, const DataType& var, int count = 1)
		{
			Insert(Begin() + index, var, count);
		}

		void InsertAt(size_t index, DataType&& var, int count = 1)
		{
			Insert(Begin() + index, std::move(var), count);
		}

		template <typename ...Args>
		DataType& Emplace(Iterator where, Args&&... args)
		{
			// find index of where iterator
			// it's necessary, because after possible reallocation
			// adress of where will be different
			size_t whereIndex = where - Begin();

			// if there is lack of place in current scope allocate a new wider one 
			if (m_Size + 1 > m_Capacity)
			{
				ReAlloc(m_Size + m_Size / 2);

				//reassign where pointer
				where = &m_Data[whereIndex];
			}

			if (where != End())
			{
				// call default constructors at the new last elements
				new (&m_Data[m_Size]) DataType(std::move(*(End() - 1)));

				// move elements using move assignment
				for (Iterator bottomIt = End() - 2, topIt = End() - 1;
					topIt != where;
					bottomIt--, topIt--)
				{
					*topIt = std::move(*bottomIt);
				}
			}

			// finally assign new value to prepared place
			new(&m_Data[whereIndex]) DataType(std::forward<Args>(args)...);

			return m_Data[m_Size++];
		}

		/* Operators */

		// copy assignment
		Vector& operator=(const Vector& other)
		{
			if (*this != other)
			{
				if (m_Size != other.m_Size)
					ReAlloc(other.m_Size);

				for (size_t i = 0; i < m_Size; i++)
				{
					m_Data[i].~DataType();
				}

				m_Size = other.m_Size;

				for (size_t i = 0; i < m_Size; i++)
				{
					new (&m_Data[i]) DataType(other.m_Data[i]);
				}
			}
			return *this;
		}

		// move assignment
		Vector& operator=(Vector&& other) noexcept
		{
			if (*this != other)
			{
				if (m_Size != other.m_Size)
					ReAlloc(other.m_Size);

				for (size_t i = 0; i < m_Size; i++)
				{
					m_Data[i].~DataType();
				}

				m_Size = other.m_Size;

				for (size_t i = 0; i < m_Size; i++)
				{
					new (&m_Data[i]) DataType(std::move(other.m_Data[i]));
				}
			}
			return *this;
		}

		bool operator==(const Vector& other)
		{
			if (m_Size == other.m_Size)
			{
				for (size_t i = 0; i < m_Size; i++)
				{
					if (m_Data[i] != other.m_Data[i])
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
		DataType& Front() { return m_Data[0]; }
		const DataType& Front() const { return m_Data[0]; }

		// getter/setter - getter available when vector is const (second line)
		DataType& Back() { return m_Data[m_Size - 1]; }
		const DataType& Back() const { return m_Data[m_Size - 1]; }

		// getter/setter - getter available when vector is const (second line)
		DataType& operator[](size_t index) { return m_Data[index]; }
		const DataType& operator[](size_t index) const { return m_Data[index]; } 

		// getter/setter - getter available when vector is const (second line)
		DataType* Data() { return m_Data; }
		const DataType* Data() const { return m_Data; }

		// getter (available when vector is const)
		size_t Size() const { return m_Size; }

		// getter (available when vector is const)
		size_t Capacity() const { return m_Capacity; } 

		// getter (available when vector is const)
		bool IsEmpty() const { return m_Size == 0; } 

		// for ranged loops
		
		// getting begin iterator (has to begin with small letter)
		Iterator begin() { return Iterator(m_Data); } 

		// getting end iterator (has to begin with small letter)
		Iterator end() { return Iterator(m_Data + m_Size); } 

		// default 
		
		// getting begin iterator (has to begin with small letter)
		Iterator Begin() { return Iterator(m_Data); }

		// getting end iterator (has to begin with small letter)
		Iterator End() { return Iterator(m_Data + m_Size); }
	};
}