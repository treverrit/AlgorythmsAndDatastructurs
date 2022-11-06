#include <iostream>
#include "Array.h"

constexpr size_t ARRAY_SIZE = 20;

int main()
{
	Array<int>intArray = Array<int>();
	for (size_t index = 0; index < ARRAY_SIZE; index++)
	{
		intArray.Append(static_cast<int>(index + 1));
		std::cout << intArray[index] << " "; // 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
	}

	std::cout << "\n" << intArray.Pop() << "\n";

	for (size_t index = 0; index < intArray.Size(); index++)
	{
		std::cout << intArray[index] << " "; // 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 19 ?
	}
	return 0;
}