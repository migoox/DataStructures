#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <stack>
#include <queue>
#include "../DataStructures/List.h"
#include "../DataStructures/Stack.h"
#include "../DataStructures/Queue.h"
#include "../DataStructures/Vector.h"
#include "../DataStructures/Array.h"
#include "../Other/Vector2f.h"

using DataStructures::Stack;
using DataStructures::Queue;
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

static void PrintVector(const Vector<int>& vec)
{
	std::cout << "========PRINTING VECTOR: =======\n";
	for (size_t i = 0; i < vec.Size(); i++)
	{
		const int& it = vec[i];

		std::cout << "[" << i << "]: " << it << std::endl;
	}
	std::cout << "================================\n";

}

static void PrintList(const List<Vector2f>& list, const std::string& str = "")
{
	std::cout << "========PRINTING LIST(" << str << "): =======\n";
	int i = 0;
	for (auto& it : list)
	{
		std::cout << "[" << i << "]: ";
		std::cout << it.x << ", " << it.y << std::endl;
		i++;
	}
	std::cout << "================================\n";
}

int main()
{


	return 0;
}