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
	List<Vector2f> list;

	list.PushBack(Vector2f(5, 1));
	list.EmplaceBack(3, 2);
	list.EmplaceBack(1, 2);
	list.EmplaceBack(6, 1);
	list.EmplaceBack(22, 10);
	list.EmplaceBack(8, 4);
	
	PrintList(list, "list");


	list.Erase(list.begin()+1, list.end());
	list.Insert(list.begin(), Vector2f(5), 2);
	PrintList(list, "list");

	return 0;
}