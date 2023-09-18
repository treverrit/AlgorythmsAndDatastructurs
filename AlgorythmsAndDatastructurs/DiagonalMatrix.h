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
	DiagonalMatrix(size_t dimension) noexcept : Matrix<Type>(dimension) { this->MakeDataArray(); }

	void Show() const override;
	void SetRandomDigits() override;
	void SetRandomIntegerValues(int lowerBound, int upperBound) override;
protected:
	void MakeDataArray() override;
};

template<typename Type>
inline void DiagonalMatrix<Type>::Show() const
{
	for (size_t row = 0; row < this->mDimension; ++row)
	{
		for (size_t column = 0; column < this->mDimension; ++column)
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
	for (size_t index = 0; index < this->mDimension; ++index)
	{
		this->moptrData[index] = rand() % 10;
	}
}

template<typename Type>
inline void DiagonalMatrix<Type>::SetRandomIntegerValues(int lowerBound, int upperBound)
{
	std::random_device rd;  // a seed source for the random number engine
	std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
	std::uniform_int_distribution<int> distrib(lowerBound, upperBound);
	for (size_t index = 0; index < this->mDimension; ++index)
	{
		this->moptrData[index] = distrib(gen);
	}
}

template<typename Type>
inline void DiagonalMatrix<Type>::MakeDataArray()
{
	this->moptrData = new Type[this->mDimension];
}
