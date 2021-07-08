#include <iostream>
#include <vector>
#include <list>
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
	List<int> list;
	list.Assign(5, 6);

	list.Remove(5);

	list.Assign(4, 2);
	list.Insert(list.begin() + 1, 3, 3);

	for (List<int>::Iterator it = list.begin(); 
		it != list.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;
	return 0;
}