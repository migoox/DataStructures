#pragma once

namespace Maths
{
	struct Vector2f
	{ 
		float x = 0.0f, y = 0.0f;

		int* dynamicArray;

		Vector2f()
		{
			dynamicArray = new int[5];
		}

		Vector2f(float value)
			: x(value), y(value)
		{
			dynamicArray = new int[5];
		}

		Vector2f(float x, float y) 
			: x(x), y(y) 
		{ 
			dynamicArray = new int[5];
		}
			
		Vector2f(const Vector2f& other) // copy constructor
			: x(other.x), y(other.y)
		{
			std::cout << "CONSTRUCTOR: COPY\n";
			dynamicArray = new int[5];

			for (size_t i = 0; i < 5; i++)
			{
				dynamicArray[i] = other.dynamicArray[i];
			}
		}

		Vector2f(Vector2f&& other) noexcept // move constructor
			: x(other.x), y(other.y)
		{
			std::cout << "MOVE\n";
			dynamicArray = other.dynamicArray;
			other.dynamicArray = nullptr;
		}

		~Vector2f() // destructor
		{
			std::cout << "DESTROY x=" << x << "  y=" << y << "\n";
			delete[] dynamicArray;
		}

		Vector2f& operator=(const Vector2f& other) // copy assigment
		{
			std::cout << "COPY\n";
			if (other.x != x || other.y != y)
			{
				x = other.x;
				y = other.y;

				for (size_t i = 0; i < 5; i++)
				{
					dynamicArray[i] = other.dynamicArray[i];
				}
			}
			return *this;
		}

		Vector2f& operator=(Vector2f&& other) noexcept // move assigment
		{
			std::cout << "MOVE\n";
			if (other.x != x || other.y != y)
			{
				x = other.x;
				y = other.y;
				
				dynamicArray = other.dynamicArray;
				other.dynamicArray = nullptr;
			}
			return *this;
		}

		friend Vector2f operator+(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.x + right.x, left.y + right.y);
		}

		friend Vector2f operator+(const Vector2f& left, float right)
		{
			return Vector2f(left.x + right, left.y + right);
		}

		friend Vector2f operator+(float left, const Vector2f& right)
		{
			return Vector2f(left+ right.x, left + right.y);
		}

		friend Vector2f operator*(const Vector2f& left, const Vector2f& right)
		{
			return Vector2f(left.x * right.x, left.y * right.y);
		}

		friend Vector2f operator*(const Vector2f& left, float right)
		{
			return Vector2f(left.x * right, left.y * right);
		}

		friend Vector2f operator*(float left, const Vector2f& right)
		{
			return Vector2f(left * right.x, left * right.y);
		}

		bool operator==(const Vector2f& other)
		{
			return x == other.x && y == other.y;
		}

		bool operator!=(const Vector2f& other)
		{
			return !(*this == other);
		}

	};
}