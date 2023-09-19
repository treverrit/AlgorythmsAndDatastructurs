#pragma once
#include "Matrix.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <random>

template <typename Type>
class DiagonalMatrix : public Matrix<Type>
{
public:
	DiagonalMatrix(size_t dimension) noexcept : Matrix<Type>(dimension) {}

	void Show() const override;
	void SetRandomDigits() override;
	void SetRandomIntegerValues(int lowerBound, int upperBound) override;
};

template<typename Type>
inline void DiagonalMatrix<Type>::Show() const
{
	for (size_t row = 0; row < this->mArraySize; ++row)
	{
		for (size_t column = 0; column < this->mArraySize; ++column)
		{
			if (row == column) 
			{
				std::cout << this->moptrData[column] << " ";
			} 
			else
			{
				std::cout << 0 << " ";
			}
		}
		std::cout << std::endl;
	}
}

template<typename Type>
inline void DiagonalMatrix<Type>::SetRandomDigits()
{
	for (size_t index = 0; index < this->mArraySize; ++index)
	{
		this->moptrData[index] = 1 + rand() % 9;
	}
}

template<typename Type>
inline void DiagonalMatrix<Type>::SetRandomIntegerValues(int lowerBound, int upperBound)
{
	std::random_device rd;  // a seed source for the random number engine
	std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> distrib(lowerBound, upperBound);
	for (size_t index = 0; index < this->mArraySize; ++index)
	{
		this->moptrData[index] = distrib(gen);
	}
}
