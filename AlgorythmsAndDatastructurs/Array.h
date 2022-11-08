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

template<typename Type>
concept IsNumeric = std::integral<Type> || std::floating_point<Type>;

template<typename Type>
class Array
{
public:
	// constructors
	Array() noexcept : mSize(0), mCapacity(1), moptrData(new Type) {}
	Array(size_t capacity) noexcept : mSize(0), mCapacity(capacity), moptrData(new Type[mCapacity]) {}

	// destructor
	~Array() noexcept { delete[] moptrData; moptrData = nullptr; }

	inline size_t Size() const { return mSize; }

	// access operators
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
private:
	// resize the array because it is a dynamic array
	void Resize(size_t newCapacity);

private:
	size_t mSize;
	size_t mCapacity;
	Type* moptrData;
};

template<typename Type>
inline const Type Array<Type>::operator[](size_t index) const
{
	assert(index < mSize); 
	if (index < mSize)
	{
		return moptrData[index];
	}
}

template<typename Type>
inline Type& Array<Type>::operator[](size_t index)
{
	assert(index < mSize);
	if (index < mSize) 
	{ 
		return moptrData[index]; 
	}
}

template<typename Type>
inline void Array<Type>::Append(Type item)
{
	// if the array is full make the array bigger
	if (mSize == mCapacity) 
	{ 
		Resize(mCapacity * 2); 
	}
	moptrData[mSize] = item;
	mSize++;
}

template<typename Type>
inline Type Array<Type>::Pop()
{
	// if the size is to small make the array smaller
	if (mSize < (mCapacity / 4)) 
	{ 
		Resize(mCapacity / 2); 
	}
	mSize--;
	return moptrData[mSize];
}

template<typename Type>
inline void Array<Type>::Insert(Type item, size_t place)
{
	// if the array is full make the array bigger
	if (mSize == mCapacity)
	{
		Resize(mCapacity * 2);
	}

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
	if (mSize < (mCapacity / 4)) 
	{
		Resize(mCapacity / 2);
	}

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
		if (moptrData[index] == item)
		{
			return index;
		}
	}
	return -1;
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
