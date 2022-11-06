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

	intArray.Pop();

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " ";
	}
	return 0;
}