#pragma once
#include <iostream>
template<typename Type>
class Matrix
{
public:
	Matrix(size_t dimension) noexcept : mArraySize(dimension), moptrData(new Type[dimension]) { std::cout << mArraySize << std::endl; }
	virtual ~Matrix() noexcept { delete[] moptrData; moptrData = nullptr; }

	virtual void Show() const = 0;
	virtual void SetRandomDigits() = 0;
	virtual void SetRandomIntegerValues(int lowerBound, int upperBound) = 0;
protected:
	size_t mArraySize;
	Type* moptrData;
};