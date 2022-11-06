#pragma once

//============================================================================
// Name        : Array.h
// Author      : Gerrit Flick
// Version     : 1.0
// Copyright   : 
// Description : A resizable array template
//============================================================================

#include <cassert>

template<typename Type>
class Array
{
public:
	// constructors
	constexpr Array() noexcept : mSize(0), mCapacity(1), moptrData(new Type[mCapacity]) {}
	constexpr Array(size_t capacity) noexcept : mSize(0), mCapacity(capacity), moptrData(new Type[mCapacity]) {}

	// destructor
	~Array() noexcept { delete[] moptrData; }

	//access operators
	const Type operator [] (size_t index) const;
	Type& operator [] (size_t index);

	// simple push and pop fuctions
	void Append(Type item);
	void Pop();
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
	std::assert(mSize < index);
	if (mSize < index) { return moptrData[index]; }
}

template<typename Type>
inline Type& Array<Type>::operator[](size_t index)
{
	std::assert(mSize < index);
	if (mSize < index) { return moptrData[index]; }
}

template<typename Type>
inline void Array<Type>::Append(Type item)
{
	if (mSize == mCapacity) { Resize(mCapacity * 2); }
	moptrData[mSize] = item;
	mSize++;
}

template<typename Type>
inline void Array<Type>::Pop()
{
	if (mSize < mCapacity / 4) { Resize(mCapacity / 2); }
	mSize--;
}

template<typename Type>
inline void Array<Type>::Resize(size_t newCapacity)
{
	Type* mnoptrNewData = new Type[newCapacity];

	for (size_t index = 0; index < mSize; index++)
	{
		mnoptrNewData[index] = moptrData[index];
	}

	delete[] moptrData;
	moptrData = mnoptrNewData;
	mCapacity = newCapacity;
}
