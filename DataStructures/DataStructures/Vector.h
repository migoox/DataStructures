#pragma once

namespace DataStructures
{
	template <typename MyVector>
	class VectorConstIterator
	{
	public:
		using DataType = typename MyVector::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;
		using PointerType = DataType*;
		using ConstPointerType = const DataType*;

	public:
		PointerType _Ptr;

	public:
		VectorConstIterator() noexcept
			: _Ptr(nullptr)
		{
		}

		explicit VectorConstIterator(PointerType ptr) noexcept
			: _Ptr(ptr)
		{
		}

		VectorConstIterator(const VectorConstIterator& other) noexcept
			: _Ptr(other._Ptr)
		{
		}

		PointerType operator->() const
		{
			return _Ptr;
		}

		ConstReferenceType operator*() const
		{
			return *(_Ptr);
		}

		ConstReferenceType operator[](size_t index)
		{
			return *(_Ptr + index);
		}

		VectorConstIterator operator++()
		{
			_Ptr++;
			return *this;
		}

		VectorConstIterator operator++(int)
		{
			VectorConstIterator temp = *this;
			_Ptr++;
			return temp;
		}

		VectorConstIterator operator--()
		{
			_Ptr--;
			return *this;
		}

		VectorConstIterator operator--(int)
		{
			VectorConstIterator temp = *this;
			_Ptr--;
			return temp;
		}

		VectorConstIterator operator+=(size_t right)
		{
			_Ptr += right;
			return *this;
		}

		VectorConstIterator operator-=(size_t right)
		{
			_Ptr -= right;
			return *this;
		}

		VectorConstIterator operator+(size_t right)
		{
			VectorConstIterator temp = *this;
			temp._Ptr = temp._Ptr + right;
			return temp;
		}

		VectorConstIterator operator-(size_t right)
		{
			VectorConstIterator temp = *this;
			temp._Ptr = temp._Ptr - right;
			return temp;
		}

		size_t operator-(const VectorConstIterator& right)
		{
			return _Ptr - right._Ptr;
		}

		VectorConstIterator& operator=(const VectorConstIterator& other)
		{
			if (_Ptr != other._Ptr)
			{
				_Ptr = other._Ptr;
			}
			return *this;
		}

		VectorConstIterator& operator=(ConstPointerType ptr)
		{
			if (_Ptr != ptr)
			{
				_Ptr = ptr;
			}
			return *this;
		}

		VectorConstIterator& operator=(PointerType ptr)
		{
			if (_Ptr != ptr)
			{
				_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const VectorConstIterator& other)
		{
			return _Ptr == other._Ptr;
		}

		bool operator!=(const VectorConstIterator& other)
		{
			return !(_Ptr == other._Ptr);
		}
	};

	template <typename MyVector>
	class VectorIterator : public VectorConstIterator<MyVector>
	{
	public:
		using MyBase = VectorConstIterator<MyVector>;

		using DataType = typename MyVector::DataType;
		using ReferenceType = DataType&;
		using PointerType = DataType*;

		using MyBase::MyBase;

	public:

		PointerType operator->() 
		{
			return MyBase::_Ptr;
		}

		ReferenceType operator*()
		{
			return *(MyBase::_Ptr);
		}

		ReferenceType operator[](size_t index)
		{
			return *(MyBase::_Ptr + index);
		}

		VectorIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		VectorIterator operator++(int)
		{
			VectorIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		VectorIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		VectorIterator operator--(int)
		{
			VectorIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		VectorIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		VectorIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		VectorIterator operator+(size_t right)
		{
			VectorIterator temp = *this;
			temp += right;
			return temp;
		}

		VectorIterator operator-(size_t right)
		{
			VectorIterator temp = *this;
			temp -= right;
			return temp;
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const VectorIterator& right)
		{
			return MyBase::operator-(right);
		}

		VectorIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}
	};

	template <typename MyVector>
	class VectorConstReversedIterator
	{
	public:
		using DataType = typename MyVector::DataType;
		using ReferenceType = DataType&;
		using ConstReferenceType = const DataType&;
		using PointerType = DataType*;
		using ConstPointerType = const DataType*;

	private:
		ConstPointerType _Ptr;

	public:
		VectorConstReversedIterator() noexcept
			: _Ptr(nullptr)
		{
		}

		explicit VectorConstReversedIterator(ConstPointerType ptr) noexcept
			: _Ptr(ptr)
		{
		}

		VectorConstReversedIterator(const VectorConstReversedIterator& other) noexcept
			: _Ptr(other._Ptr)
		{
		}

		ConstPointerType operator->() const
		{
			return _Ptr;
		}

		ConstReferenceType operator*() const
		{
			return *(_Ptr);
		}

		ConstReferenceType operator[](size_t index)
		{
			return *(_Ptr + index);
		}

		VectorConstReversedIterator operator++()
		{
			_Ptr--;
			return *this;
		}

		VectorConstReversedIterator operator++(int)
		{
			VectorConstReversedIterator temp = *this;
			_Ptr--;
			return temp;
		}

		VectorConstReversedIterator operator--()
		{
			_Ptr++;
			return *this;
		}

		VectorConstReversedIterator operator--(int)
		{
			VectorConstReversedIterator temp = *this;
			_Ptr++;
			return temp;
		}

		VectorConstReversedIterator operator+=(size_t right)
		{
			_Ptr -= right;
			return *this;
		}

		VectorConstReversedIterator operator-=(size_t right)
		{
			_Ptr += right;
			return *this;
		}

		VectorConstReversedIterator operator+(size_t right)
		{
			VectorConstReversedIterator temp = *this;
			temp._Ptr = temp._Ptr - right;
			return temp;
		}

		VectorConstReversedIterator operator-(size_t right)
		{
			VectorConstReversedIterator temp = *this;
			temp._Ptr = temp._Ptr + right;
			return temp;
		}

		size_t operator-(const VectorConstReversedIterator& right)
		{
			return _Ptr - right._Ptr;
		}

		VectorConstReversedIterator& operator=(const VectorConstReversedIterator& other)
		{
			if (_Ptr != other._Ptr)
			{
				_Ptr = other._Ptr;
			}
			return *this;
		}

		VectorConstReversedIterator& operator=(ConstPointerType ptr)
		{
			if (_Ptr != ptr)
			{
				_Ptr = ptr;
			}
			return *this;
		}

		VectorConstReversedIterator& operator=(PointerType ptr)
		{
			if (_Ptr != ptr)
			{
				_Ptr = ptr;
			}
			return *this;
		}

		bool operator==(const VectorConstReversedIterator& other)
		{
			return _Ptr == other._Ptr;
		}

		bool operator!=(const VectorConstReversedIterator& other)
		{
			return !(_Ptr == other._Ptr);
		}
	};

	template <typename MyVector>
	class VectorReversedIterator : public VectorConstReversedIterator<MyVector>
	{
	public:
		using MyBase = VectorConstReversedIterator<MyVector>;

		using DataType = typename MyVector::DataType;
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

		VectorReversedIterator operator++()
		{
			MyBase::operator++();
			return *this;
		}

		VectorReversedIterator operator++(int)
		{
			VectorReversedIterator temp = *this;
			MyBase::operator++();
			return temp;
		}

		VectorReversedIterator operator--()
		{
			MyBase::operator--();
			return *this;
		}

		VectorReversedIterator operator--(int)
		{
			VectorReversedIterator temp = *this;
			MyBase::operator--();
			return temp;
		}

		VectorReversedIterator operator+=(size_t right)
		{
			MyBase::operator+=(right);
			return *this;
		}

		VectorReversedIterator operator-=(size_t right)
		{
			MyBase::operator-=(right);
			return *this;
		}

		VectorReversedIterator operator+(size_t right)
		{
			VectorReversedIterator temp = *this;
			temp += right;
			return temp;
		}

		VectorReversedIterator operator-(size_t right)
		{
			VectorReversedIterator temp = *this;
			temp -= right;
			return temp;
		}

		size_t operator-(const MyBase& right)
		{
			return MyBase::operator-(right);
		}

		size_t operator-(const VectorReversedIterator& right)
		{
			return MyBase::operator-(right);
		}

		VectorReversedIterator& operator=(PointerType ptr)
		{
			MyBase::operator=(ptr);
			return *this;
		}
	};

	template <typename T>
	class Vector
	{
	public:
		using DataType = T;

		using ConstIterator = VectorConstIterator<Vector<DataType>>;
		using Iterator = VectorIterator<Vector<DataType>>;

		using ConstReversedIterator = VectorConstReversedIterator<Vector<DataType>>;
		using ReversedIterator = VectorReversedIterator<Vector<DataType>>;

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

		// initializer list constructor
		Vector(std::initializer_list<DataType> list)
		{
			// allocating enough memory to move all of the data (capacity is described)
			ReAlloc(list.size());

			// saving size
			m_Size = list.size();

			// moving
			int i = 0;
			for (auto& it : list)
			{
				new (&m_Data[i]) DataType(std::move(it));
				i++;
			}
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

		void Erase(ConstIterator where)
		{
			Iterator _where(where._Ptr);

			// deleting element
			(*_where).~DataType();

			// moving elements to make vector contiguous
			Iterator current = _where;
			for (Iterator it = _where + 1; it != end(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_Size--;
		}

		// first inclusive and last exclusive
		void Erase(ConstIterator first, ConstIterator last)
		{
			Iterator _first(first._Ptr);
			Iterator _last(last._Ptr);

			size_t count = 0;

			// deleting elements
			for (Iterator it = _first; it != _last; it++)
			{
				(*it).~DataType();
				count++;
			}
			
			// moving elements to make vector contiguous
			Iterator current = _first;
			for (Iterator it = _last; it != end(); it++)
			{
				*current = std::move(*it);
				current++;
			}

			m_Size -= count;
		}

		void Insert(ConstIterator where, const DataType& var, int count = 1)
		{
			Iterator _where(where._Ptr);

			// find index of where iterator
			// it's necessary, because after possible reallocation
			// adress of where will be different
			size_t whereIndex = where - begin();

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
				new (&m_Data[whereIndex + i]) DataType(var);

			// increase the size by one
			m_Size += count;
		}

		template <typename ...Args>
		DataType& Emplace(Iterator where, Args&&... args)
		{
			// find index of where iterator
			// it's necessary, because after possible reallocation
			// adress of where will be different
			size_t whereIndex = where - begin();

			// if there is lack of place in current scope allocate a new wider one 
			if (m_Size + 1 > m_Capacity)
			{
				ReAlloc(m_Size + m_Size / 2);

				//reassign where pointer
				where = &m_Data[whereIndex];
			}

			if (where != end())
			{
				// call default constructors at the new last elements
				new (&m_Data[m_Size]) DataType(std::move(*(end() - 1)));

				// move elements using move assignment
				for (Iterator bottomIt = end() - 2, topIt = end() - 1;
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

		// default iterators
		Iterator begin() { return Iterator(m_Data); }
		ConstIterator begin() const { return ConstIterator(m_Data); }

		Iterator end() { return Iterator(m_Data + m_Size); }
		ConstIterator end() const { return ConstIterator(m_Data + m_Size); }

		// reversed iterators
		ReversedIterator rbegin() { return ReversedIterator(m_Data + m_Size - 1); }
		ConstReversedIterator rbegin() const { return ConstReversedIterator(m_Data + m_Size - 1); }

		ReversedIterator rend() { return ReversedIterator(m_Data - 1); }
		ConstReversedIterator rend() const { return ConstReversedIterator(m_Data - 1); }

		// const iterators
		ConstIterator cbegin() const { return ConstIterator(m_Data); }
		ConstIterator cend() const { return ConstIterator(m_Data + m_Size); }

		ConstReversedIterator crbegin() const { return ConstReversedIterator(m_Data + m_Size - 1); }
		ConstReversedIterator crend() const { return ConstReversedIterator(m_Data - 1); }
	};
}