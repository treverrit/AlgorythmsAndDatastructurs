#include <iostream>
#include "Array.h"
#include "ArrayUtils.h"

constexpr size_t ARRAY_SIZE = 20;

int main()
{
	srand(static_cast<uint32_t>(time(nullptr)));
	ArrayUtils::Test();
	return 0;
}