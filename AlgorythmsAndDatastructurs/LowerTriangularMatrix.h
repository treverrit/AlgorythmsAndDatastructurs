#pragma once
#include "Matrix.h"
#include <cstdlib>
#include <time.h>
#include <random>
#include <iostream>

template <typename Type>
class LowerTriangularMatrix : public Matrix<Type>
{
public:
	LowerTriangularMatrix(size_t dimension) noexcept;

	void SetRandomDigits() override;
	void SetRandomIntegerValues(int lowerBound, int upperBound) override;

	void Show() const override;
private:
	size_t mDimension;
};

template<typename Type>
inline LowerTriangularMatrix<Type>::LowerTriangularMatrix(size_t dimension) noexcept
	: Matrix<Type>((dimension * (dimension + 1) / 2))
	, mDimension(dimension)
{}

template<typename Type>
inline void LowerTriangularMatrix<Type>::SetRandomDigits()
{
	for (size_t index = 0; index < this->mArraySize; ++index)
	{
		this->moptrData[index] =  1+ rand() % 9;
	}

	for (size_t index = 0; index < this->mArraySize; ++index)
	{
		std::cout << this->moptrData[index] << " ";
	}
	std::cout << std::endl;
}

template<typename Type>
inline void LowerTriangularMatrix<Type>::SetRandomIntegerValues(int lowerBound, int upperBound)
{
	std::random_device rd;  // a seed source for the random number engine
	std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> distrib(lowerBound, upperBound);
	for (size_t index = 0; index < this->mArraySize; ++index)
	{
		this->moptrData[index] = distrib(gen);
	}
}

template<typename Type>
inline void LowerTriangularMatrix<Type>::Show() const
{
	for (size_t row = 1; row <= mDimension; ++row)
	{
		for (size_t column = 1; column <= mDimension; ++column)
		{
			if (row >= column)
			{
				std::cout << this->moptrData[row * (row - 1) / 2 + column - 1] << " ";
			}
			else
			{
				std::cout << 0 << " ";
			}
		}
		std::cout << std::endl;
	}
}
