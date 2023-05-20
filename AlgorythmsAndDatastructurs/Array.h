#pragma once

//============================================================================
// Name        : Array.h
// Author      : Gerrit Flick
// Version     : 1.0
// Copyright   : 
// Description : A resizable dynamic array template
//============================================================================

#include <cassert>
#include <concepts>
#include <utility>
#include <iostream>

template<typename Type>
concept IsNumeric = std::integral<Type> || std::floating_point<Type>;

enum class SortPriority{OBJECTS, SMALL_NUMBERS, BIG_NUMBERS};

template<typename Type>
class Array
{
public:
	// constructors
	Array() noexcept : mSize(0), mCapacity(1), moptrData(new Type) {}
	Array(size_t capacity) noexcept : mSize(0), mCapacity(capacity), moptrData(new Type[mCapacity]) {}

	// copy constructors
	Array(const Array& other) noexcept : mSize(other.mSize), mCapacity(other.mCapacity), moptrData(other.moptrData) {}
	Array& operator = (const Array& other) noexcept;

	// move constructors
	Array(Array&& other) noexcept;
	Array& operator = (Array&& other) noexcept;

	// destructor
	~Array() noexcept { delete[] moptrData; moptrData = nullptr; }

	inline size_t Size() const { return mSize; };
	inline size_t Capacity() const { return mCapacity; }

	// comparison operators
	bool operator == (const Array& other) const;
	bool operator != (const Array& other) const;
	// access operators

	Array operator + (const Array& other) const requires IsNumeric<Type>;
	Array operator - (const Array& other) const requires IsNumeric<Type>;
	Array& operator += (const Array& other) requires IsNumeric<Type>;
	Array& operator -= (const Array& other) requires IsNumeric<Type>;

	Array operator * (const Type& scalar) const requires IsNumeric<Type>;
	Array operator / (const Type& scalar) const requires IsNumeric<Type>;
	Array& operator *= (const Type& scalar) requires IsNumeric<Type>;
	Array& operator /= (const Type& scalar) requires IsNumeric<Type>;

	const Type operator [] (size_t index) const;
	Type& operator [] (size_t index);

	// simple push and pop fuctions
	void Append(Type item);
	Type Pop();

	// functions to remove or insert items from everywere
	void Insert(Type item, size_t place);
	Type Remove(size_t place);

	// function to find a number in the array
	long long FindNumber(Type item) const requires IsNumeric<Type>;

	// find any item in the array not very efficient O(n)
	// TODO: learn more efficient search techniques
	long long FindItem(Type item) const;

	// some stat functions
	Type Sum() const requires IsNumeric<Type>;
	double Average() const requires IsNumeric<Type>;
	double Median() const requires IsNumeric<Type>;

	// some functions to insert an another array
	void Concat(const Array& other);
	void Merge(const Array& other);
	Array& Concat(const Array& other) const;
	Array& Merge(const Array& other) const;

	// function to reverse an array
	void Reverse();

	// function for display
	void Show();

	void Sort(SortPriority = SortPriority::OBJECTS);

	// function for checking if sorted
	inline bool IsSorted() const { return IsSorted(moptrData); }
private:
	void InsertionSort();
	void MergeSort();
	void RadixSort();
	void CountSort();

	bool IsSorted(Type*) const requires IsNumeric<Type>;
	// resize the array because it is a dynamic array
	void Resize(size_t newCapacity);

	void CopyArray(const Array& other);

	void Swap(Type& x, Type& y);
private:
	size_t mSize;
	size_t mCapacity;
	Type* moptrData;
};

template<typename Type>
inline Array<Type>& Array<Type>::operator=(const Array& other) noexcept
{
	if (*this == other)
	{
		return *this;
	}
	if (moptrData)
	{
		delete[] moptrData;
		mSize = 0;
		mCapacity = 0;
		CopyArray();
	}

	return *this;
}

template<typename Type>
inline Array<Type>::Array(Array&& other) noexcept
	: mSize(other.mSize)
	, mCapacity(other.mCapacity)
	, moptrData(other.moptrData)
{
	other.mSize = 0;
	other.mCapacity = 0;
	other.moptrData = nullptr;
}

template<typename Type>
inline Array<Type>& Array<Type>::operator=(Array&& other) noexcept
{
	if (*this != other)
	{
		delete[] moptrData;

		moptrData = other.moptrData;
		mSize = other.mSize;
		mCapacity = other.mCapacity;

		other.moptrData = nullptr;
		other.mSize = 0;
		other.mCapacity = 0;
	}

	return *this;
}

template<typename Type>
inline bool Array<Type>::operator==(const Array& other) const
{
	if (mSize != other.mSize) { return false; }
	for (size_t index = 0; index < mSize; index++)
	{
		if (moptrData[index] != other.moptrData[index]) { return false; }
	}
	return true;
}

template<typename Type>
inline bool Array<Type>::operator!=(const Array& other) const
{
	return !(*this == other);
}

template<typename Type>
inline Array<Type> Array<Type>::operator+(const Array& other) const requires IsNumeric<Type>
{
	Array<Type> thisVec = *this;

	for (size_t index = 0; index < mSize; ++index)
	{
		thisVec[index] = thisVec[index] + other[index];
	}

	return thisVec;
}

template<typename Type>
inline Array<Type> Array<Type>::operator-(const Array& other) const requires IsNumeric<Type>
{
	Array<Type> thisVec = *this;

	for (size_t index = 0; index < mSize; ++index)
	{
		thisVec[index] = thisVec[index] - other[index];
	}
	return thisVec;
}

template<typename Type>
inline Array<Type>& Array<Type>::operator+=(const Array& other) requires IsNumeric<Type>
{
	*this = *this + other;
	return *this;
}

template<typename Type>
inline Array<Type>& Array<Type>::operator-=(const Array& other) requires IsNumeric<Type>
{
	*this = *this + other;
	return *this;
}

template<typename Type>
inline Array<Type> Array<Type>::operator*(const Type& scalar) const requires IsNumeric<Type>
{
	Array<Type> thisVec = *this;

	for (size_t index = 0; index < mSize; ++index)
	{
		thisVec[index] = thisVec[index] * scalar;
	}

	return thisVec;
}

template<typename Type>
inline Array<Type> Array<Type>::operator/(const Type& scalar) const requires IsNumeric<Type>
{
	Array<Type> thisVec = *this;

	for (size_t index = 0; index < mSize; ++index)
	{
		thisVec[index] = thisVec[index] / scalar;
	}

	return thisVec;
}

template<typename Type>
inline Array<Type>& Array<Type>::operator*=(const Type& scalar) requires IsNumeric<Type>
{
	*this = *this * scalar;
	return *this;
}

template<typename Type>
inline Array<Type>& Array<Type>::operator/=(const Type& scalar) requires IsNumeric<Type>
{
	*this = *this / scalar;
	return *this;
}

template<typename Type>
inline const Type Array<Type>::operator[](size_t index) const
{
	assert(index < mSize); 
	if (index < mSize) { return moptrData[index]; }
}

template<typename Type>
inline Type& Array<Type>::operator[](size_t index)
{
	assert(index < mSize);
	if (index < mSize) { return moptrData[index]; }
}

template<typename Type>
inline void Array<Type>::Append(Type item)
{
	// if the array is full make the array bigger
	if (mSize == mCapacity)  { Resize(mCapacity * 2); }
	moptrData[mSize] = item;
	mSize++;
}

template<typename Type>
inline Type Array<Type>::Pop()
{
	// if the size is to small make the array smaller
	if (mSize < (mCapacity / 4)) { Resize(mCapacity / 2); }
	mSize--;
	return moptrData[mSize];
}

template<typename Type>
inline void Array<Type>::Insert(Type item, size_t place)
{
	// if the array is full make the array bigger
	if (mSize == mCapacity) { Resize(mCapacity * 2); }

	for (size_t index = mSize; index > place; index--)
	{
		moptrData[index] = moptrData[index - 1]; // shift the data after the place where the new item should be inserted once further
	}

	moptrData[place] = item;
	mSize++;
}

template<typename Type>
inline Type Array<Type>::Remove(size_t place)
{
	// if the size is to small make the array smaller
	if (mSize < (mCapacity / 4)) { Resize(mCapacity / 2); }

	Type item = moptrData[place];

	for (size_t index = place; index < mSize - 1; index++)
	{
		moptrData[index] = moptrData[index + 1]; // shift the data after the removed item once back
	}

	mSize--;

	return item;
}

template<typename Type>
inline long long Array<Type>::FindNumber(Type item) const requires IsNumeric<Type>
{
	size_t low = 0, high = mSize, mid;

	if (!IsSorted(moptrData)) { return FindItem(item); }

	while (low <= high)
	{
		mid = (low + high) / 2;
		if (item == moptrData[mid]) // found
		{
			return mid;
		}
		else if (item < moptrData[mid]) // half the array to reduce the space
		{
			high = mid - 1; // in this case in zero direction
		}
		else
		{
			low = mid + 1; // in this case in maximum size direction
		}
	}
	return -1;
}

template<typename Type>
inline long long Array<Type>::FindItem(Type item) const
{
	for (size_t index = 0; index < mSize; index++)
	{
		if (moptrData[index] == item) { return index; }
	}
	return -1;
}

template<typename Type>
inline Type Array<Type>::Sum() const requires IsNumeric<Type>
{
	Type sum = 0;

	for (size_t index = 0; index < mSize; index++) { sum += moptrData[index]; }

	return sum;
}

template<typename Type>
inline double Array<Type>::Average() const requires IsNumeric<Type>
{
	return Sum() / (mSize * 1.0);
}

template<typename Type>
inline double Array<Type>::Median() const requires IsNumeric<Type>
{
	if (IsSorted(moptrData))
	{
		return mSize % 2 == 0 ? moptrData[mSize / 2] :
			   (moptrData[mSize / 2] + moptrData[mSize / 2 + 1]) / 2;
	}

	return 0.0;
}

template<typename Type>
inline void Array<Type>::Concat(const Array& other)
{
	size_t newSize = mSize + other.mSize;
	Type* noptrNewArray = new Type[newSize];

	for (size_t index = 0; index < mSize; ++index) // insert  the initial array in the new
	{
		noptrNewArray[index] = moptrData[index];
	}

	for (size_t index = mSize; index < newSize; ++index) // insert the other in the new
	{
		noptrNewArray[index] = other.moptrData[index - mSize];
	}

	// set the initial array to the new
	delete[] moptrData; 
	moptrData = noptrNewArray;
	mSize = newSize;
	mCapacity = newSize;
}

template<typename Type>
inline void Array<Type>::Merge(const Array& other)
{
	if (IsSorted(moptrData) && IsSorted(other.moptrData))
	{
		size_t newSize = mSize + other.mSize;
		Type* noptrNewArray = new Type[newSize];

		size_t i = 0, j = 0, k = 0;

		while (i < mSize && j < other.mSize)  
		{
			if (moptrData[i] < other.moptrData[j]) { noptrNewArray[k++] = moptrData[i++]; }
			else { noptrNewArray[k++] = other.moptrData[j++]; }
		}

		for (; i < mSize; i++) { noptrNewArray[k++] = moptrData[i]; }
		for (; j < other.mSize; j++) { noptrNewArray[k++] = other.moptrData[j]; }

		delete[] moptrData;
		moptrData = noptrNewArray;
		mSize = newSize;
		mCapacity = newSize;
	}
}

template<typename Type>
inline Array<Type>& Array<Type>::Concat(const Array& other) const
{
	size_t newSize = mSize + other.mSize;
	Array<Type>newArray = Array<Type>(newSize);

	for (size_t index = 0; index < mSize; ++index)
	{
		newArray.Append(moptrData[index]);
	}

	for (size_t index = mSize; index < newSize; ++index)
	{
		newArray.Append(moptrData[index]);
	}

	return newArray;
}

template<typename Type>
inline Array<Type>& Array<Type>::Merge(const Array& other) const
{
	size_t newSize = mSize + other.mSize;
	Array<Type> newArray = Array<Type>(newSize);

	if (IsSorted() && other.IsSorted())
	{
		size_t i = 0, j = 0;

		while (i < mSize && j < other.mSize)
		{
			if (moptrData[i] < other.moptrData[j]) { newArray.Append(moptrData[i++]); }
			else { newArray.Append(moptrData[j++]); }
		}

		for (; i < mSize; i++) { newArray.Append(moptrData[i]); }
		for (; j < other.mSize; j++) { newArray.Append(other.moptrData[j]); }
	}

	return newArray;
}

template<typename Type>
inline void Array<Type>::Reverse()
{
	for (size_t i = 0, j = mSize - 1; i < j; i++, j--)
	{
		Swap(moptrData[i], moptrData[j]);
	}
}

template<typename Type>
inline void Array<Type>::Show()
{
	std::cout << "[ ";
	for (size_t index = 0; index < mSize; index++)
	{
		std::cout << moptrData[index] << ((index < mSize - 1) ? ", " : " ]");
	}
	std::cout << std::endl;
}

template<typename Type>
inline void Array<Type>::Sort(SortPriority priority)
{
	if (priority == SortPriority::OBJECTS)
	{
		if (mSize < 1000) { InsertionSort(); }
		else { MergeSort(); }
	}
	else
	{
		if (mSize < 1000) { InsertionSort(); }
		else if (mSize < 25000) { MergeSort(); }
		else
		{
			if (priority == SortPriority::SMALL_NUMBERS) { CountSort(); }
			else { RadixSort(); }
		}
	}
}

template<typename Type>
inline void Array<Type>::InsertionSort()
{
}

template<typename Type>
inline void Array<Type>::MergeSort()
{
}

template<typename Type>
inline void Array<Type>::RadixSort()
{
}

template<typename Type>
inline void Array<Type>::CountSort()
{
}

template<typename Type>
inline bool Array<Type>::IsSorted(Type*) const requires IsNumeric<Type>
{
	for (size_t index = 0; index < mSize - 1; index++)
	{
		if (moptrData[index] > moptrData[index + 1]) { return false; }
	}
	return true;
}

template<typename Type>
inline void Array<Type>::Resize(size_t newCapacity)
{
	Type* noptrNewData = new Type[newCapacity]; // make a new array

	for (size_t index = 0; index < mSize; index++)
	{
		noptrNewData[index] = moptrData[index]; // copy the data
	}

	// give the data the member type pointer  
	delete[] moptrData;
	moptrData = noptrNewData;
	mCapacity = newCapacity;
}

template<typename Type>
inline void Array<Type>::CopyArray(const Array& other)
{
	Type* noptrNewArray = new Type[other.mSize];

	for (size_t index = 0; index < other.mSize; index++)
	{
		noptrNewArray[index] = other.moptrData[index];
	}

	moptrData = noptrNewArray;
	mSize = other.mSize;
	mCapacity = other.mCapacity;
}

template<typename Type>
inline void Array<Type>::Swap(Type& x, Type& y)
{
	Type temp = x;
	x = y;
	y = temp;
}
