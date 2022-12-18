#include <iostream>
#include "Array.h"

constexpr size_t ARRAY_SIZE = 20;

int main()
{
	Array<int>intArray = Array<int>();
	for (size_t index = 0; index < ARRAY_SIZE; index++)
	{
		intArray.Append(static_cast<int>(index + 1));
		std::cout << intArray[index] << " "; 
	}
	std::cout << "\n";
	std::cout << "\n" << intArray.Pop() << "\n";

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " ";
	}

	std::cout << "\n";
	intArray.Insert(11, 11);

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " ";
	}

	std::cout << "\n";
	intArray.Remove(14);

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " ";
	}

	std::cout << "\n" << intArray.FindNumber(15) << "\n";
	std::cout << "\n" << intArray.FindNumber(14) << "\n";

	Array<int>intArray2 = Array<int>();

	for (size_t index = 0; index < 15; index++)
	{
		intArray2.Append(static_cast<int>(index * 2));
	}

	intArray.Merge(intArray2);
	intArray.Concat(intArray2);

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " ";
	}

	return 0;
}