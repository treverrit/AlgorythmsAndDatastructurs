#include <iostream>
#include "Array.h"
#include "ArrayUtils.h"
#include "LinkedListUtils.h"
#include "DiagonalMatrix.h"

constexpr size_t ARRAY_SIZE = 20;

int main()
{
	srand(static_cast<uint32_t>(time(nullptr)));
	ArrayUtils::Test();
	LinkedListTest();
	DiagonalMatrix<int>matrix{5};
	matrix.SetRandomDigits();
	matrix.Show();
	DiagonalMatrix<int>matrix2{5};
	matrix.SetRandomIntegerValues(50, 100);
	matrix.Show();
	return 0;
}