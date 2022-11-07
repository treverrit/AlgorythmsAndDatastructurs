#pragma once

//============================================================================
// Name        : Array.h
// Author      : Gerrit Flick
// Version     : 1.0
// Copyright   : 
// Description : A resizable dynamic array template
//============================================================================

#include <cassert>

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
	if (mSize == mCapacity)
	{
		Resize(mCapacity * 2)
	}

	for (size_t index = mSize; index > place; index--)
	{
		moptrData[index] = moptrData[index - 1];
	}

	moptrData[place] = item;
	mSize++;
}

template<typename Type>
inline Type Array<Type>::Remove(size_t place)
{
	if (mSize < (mCapacity / 4))
	{
		Resize(mCapacity / 2);
	}

	Type item = moptrData[place];

	for (size_t index = place; index < mSize - 1; index++)
	{
		moptrData[index] = moptrData[index + 1];
	}

	mSize--;

	return item;
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
