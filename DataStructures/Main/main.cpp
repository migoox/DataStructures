#include <iostream>
#include <vector>
#include <array>
#include "../DataStructures/List.h"
#include "../DataStructures/LStack.h"
#include "../DataStructures/Stack.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Array.h"
#include "../Other/Vector2f.h"

using DataStructures::LStack;
using DataStructures::Stack;
using DataStructures::List;
using DataStructures::Vector;
using DataStructures::Array;
using Maths::Vector2f;

static void PrintVector(const Vector<Vector2f>& vec)
{
	std::cout << "========PRINTING VECTOR: =======\n";
	for (size_t i = 0; i < vec.Size(); i++)
	{
		const Vector2f& it = vec[i];

		std::cout << "["<< i << "]: "<< it.x << ", " << it.y << std::endl;
	}
	std::cout << "================================\n";
}

static void PrintVector(const Vector<std::string>& vec)
{
	std::cout << "========PRINTING VECTOR: =======\n";
	for (size_t i = 0; i < vec.Size(); i++)
	{
		const std::string& it = vec[i];

		std::cout << "[" << i << "]: " << it << std::endl;
	}
	std::cout << "================================\n";

}

void test(const std::array<int, 6>::const_iterator& it)
{
	
}

int main()
{
	std::array<int, 5> arr1 = { 1,2,3,4,5 };

	std::array<int, 5>::const_iterator it = arr1.begin();

	std::cout << *it << std::endl;

	return 0;
}