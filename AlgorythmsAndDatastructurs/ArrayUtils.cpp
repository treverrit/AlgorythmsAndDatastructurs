#include "ArrayUtils.h"
#include <iostream>

void ArrayUtils::Test()
{
	MakeInstanceTest();
	AppendTest();
	InsertTest();
	PopTest();
	RemoveTest();
	FindNumberTest();
	FindItemTest();
	StatsTest();
	ConcatTest();
	MergeTest();
	ReverseTest();
	SortTest();
}

void ArrayUtils::MakeInstanceTest()
{
	Array<int> intArray{};
	std::cout << intArray.Capacity() << std::endl;
}

void ArrayUtils::AppendTest()
{
	Array<int> intArray{};
	intArray.Append(1);

	intArray.Show();

	for (size_t index = 0; index < 10; ++index)
	{
		intArray.Append(static_cast<int>(index) + 2);
	}

	intArray.Show();
}

void ArrayUtils::InsertTest()
{
	Array<int>intArray{};

	for (size_t index = 0; index < 10; ++index)
	{
		intArray.Append(static_cast<int>(index));
	}

	intArray.Show();

	for (size_t index = 0; index < 5; ++index)
	{
		intArray.Insert(100, index * 2);
	}

	intArray.Show();
}

void ArrayUtils::PopTest()
{
	Array<int>intArray{};

	for (size_t index = 0; index < 2; ++index)
	{
		intArray.Append(10);
	}

	intArray.Show();
	intArray.Pop();
	intArray.Show();
}

void ArrayUtils::RemoveTest()
{
	Array<int>intArray{};

	for(size_t index = 0; index < 10; ++index)
	{
		intArray.Append(static_cast<int>(index) + 1);
	}

	intArray.Show();
	intArray.Remove(5);
	intArray.Show();
}

// Not implemented section

void ArrayUtils::FindNumberTest()
{
	Array<int>intArray{};

	for (size_t index = 0; index < 40; ++index) {
		int item = rand() % 100;
		intArray.Append(item);
	}

	intArray.Sort();
	std::cout << ((intArray.IsSorted()) ? "true" : "false") << std::endl;
	intArray.Show();
	int numberToFind = rand() % 100;
	std::cout << numberToFind << std::endl;
	std::cout << intArray.FindNumber(numberToFind) << std::endl;
}

void ArrayUtils::FindItemTest()
{
	return;
}

void ArrayUtils::StatsTest()
{
	return;
}

void ArrayUtils::ConcatTest()
{
	return;
}

void ArrayUtils::MergeTest()
{
	return;
}

void ArrayUtils::ReverseTest()
{
	return;
}

void ArrayUtils::SortTest()
{
	Array<int>intArray{};

	for (size_t index = 0; index < 30; ++index)
	{
		intArray.Append(rand() % 250);
	}

	intArray.Show();
	intArray.Sort();
	intArray.Show();
}
