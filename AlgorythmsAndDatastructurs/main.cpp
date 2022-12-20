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
	std::cout << "\n" << intArray.Pop() << "\n";

	intArray.Show();

	intArray.Insert(11, 11);

	intArray.Show();

	intArray.Remove(14);

	intArray.Show();

	std::cout << "\n" << intArray.FindNumber(15) << "\n";
	std::cout << "\n" << intArray.FindNumber(14) << "\n";

	Array<int>intArray2 = Array<int>();

	for (size_t index = 0; index < 15; index++)
	{
		intArray2.Append(static_cast<int>(index * 2));
	}

	intArray.Merge(intArray2);
	intArray.Concat(intArray2);

	intArray.Show();

	intArray.Reverse();

	intArray.Show();

	return 0;
}