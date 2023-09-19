#include <iostream>
#include "Array.h"
#include "ArrayUtils.h"
#include "LinkedListUtils.h"
#include "DiagonalMatrix.h"
#include "LowerTriangularMatrix.h"

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
	LowerTriangularMatrix<int>matrix3{5};
	matrix3.SetRandomDigits();
	matrix3.Show();
	return 0;
}