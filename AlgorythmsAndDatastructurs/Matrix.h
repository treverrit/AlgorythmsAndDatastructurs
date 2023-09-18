#pragma once
template<typename Type>
class Matrix
{
public:
	Matrix(size_t dimension) noexcept : mDimension(dimension) {}
	virtual ~Matrix() noexcept { delete[] moptrData; moptrData = nullptr; }

	virtual void Show() const = 0;
	virtual void SetRandomDigits() = 0;
	virtual void SetRandomIntegerValues(int lowerBound, int upperBound) = 0;
protected:
	virtual void MakeDataArray() = 0;
	size_t mDimension;
	Type* moptrData;
};
