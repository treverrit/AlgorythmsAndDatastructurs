#pragma once

#include <stdint.h>
#include <cassert>
#include <iostream>

template<typename Type>
class LinkedList
{
public:
	struct Node
	{
		Type data;
		Node* next;
	};

	LinkedList() noexcept;
	LinkedList(Type data) noexcept;
	~LinkedList() noexcept;

	void Append(Type item);
	void Show() const;
	void Makeunique();
	void Reverse();
	void Concat(LinkedList& other);
	void Merge(LinkedList& other);

	inline const Type First() const { return moptrFirstNode->data; }
	inline const Type Last() const { return moptrLastNode->data; }
private:
	Node* moptrFirstNode;
	Node* moptrLastNode;
	size_t mSize;
};

template<typename Type>
inline LinkedList<Type>::LinkedList() noexcept
	:moptrFirstNode(nullptr)
	,moptrLastNode(nullptr)
	,mSize(0)
{}

template<typename Type>
inline LinkedList<Type>::LinkedList(Type data) noexcept
	:moptrFirstNode(new Node)
{
	moptrFirstNode->data = data;
	moptrFirstNode->next = nullptr;
	moptrLastNode = moptrFirstNode;
	mSize = 1;
}

template<typename Type>
inline LinkedList<Type>::~LinkedList() noexcept
{
	Node* temp = moptrFirstNode;

	while (temp)
	{
		moptrFirstNode = moptrFirstNode->next;
		delete temp;
		temp = moptrFirstNode;
	}
}

template<typename Type>
inline void LinkedList<Type>::Append(Type item)
{
	if (moptrFirstNode)
	{
		Node* append = new Node;
		append->data = item;

		moptrLastNode->next = append;
		moptrLastNode = append;
		moptrLastNode->next = nullptr;
	}
	else
	{
		moptrFirstNode = new Node;
		moptrFirstNode->data = item;
		moptrFirstNode->next = nullptr;
		moptrLastNode = moptrFirstNode;
	}

	mSize++;
}

template<typename Type>
inline void LinkedList<Type>::Show() const
{
	Node* temp = moptrFirstNode;
	
	std::cout << "[ ";

	while (temp)
	{
		std::cout << temp->data << ((temp->next != nullptr) ? ", " : " ");
		temp = temp->next;
	}

	std::cout << "]" << std::endl;
}

template<typename Type>
inline void LinkedList<Type>::Makeunique()
{
	Node* temp = moptrFirstNode->next;
	Node* current = moptrFirstNode;

	while (temp)
	{
		if (temp->data != current->data)
		{
			current = temp;
			temp = temp->next;
		}
		else
		{
			current->next = temp->next;
			delete temp;
			temp = current->next;
			mSize--;
		}
	}
}

template<typename Type>
inline void LinkedList<Type>::Reverse()
{
	Node* q = nullptr, *r = nullptr;
	Node* p = moptrFirstNode;

	while (p)
	{
		r = q;
		q = p;
		p = p->next;
		q->next = r;
	}
	moptrFirstNode = q;
}

template<typename Type>
inline void LinkedList<Type>::Concat(LinkedList& other)
{
	moptrLastNode->next = other.moptrFirstNode;
	moptrLastNode = other.moptrLastNode;
	mSize += other.mSize;
	other.moptrFirstNode = nullptr;
}

template<typename Type>
inline void LinkedList<Type>::Merge(LinkedList& other)
{
	Node* thisNode = moptrFirstNode;
	Node* otherNode = other.moptrFirstNode;
	Node* iterationNode;
	Node* mergeNode;

	if (thisNode->data < otherNode->data)
	{
		mergeNode = iterationNode = thisNode;
		thisNode = thisNode->next;
		mergeNode->next = nullptr;
	}
	else
	{
		mergeNode = iterationNode = otherNode;
		otherNode = otherNode->next;
		mergeNode->next = nullptr;
	}

	while (thisNode && otherNode)
	{
		if (thisNode->data < otherNode->data)
		{
			iterationNode->next = thisNode;
			iterationNode = thisNode;
			thisNode = thisNode->next;
			iterationNode->next = nullptr;
		}
		else
		{
			iterationNode->next = otherNode;
			iterationNode = otherNode;
			otherNode = otherNode->next;
			iterationNode->next = nullptr;
		}
	}

	if (thisNode) 
	{ 
		iterationNode->next = thisNode;
		moptrFirstNode = mergeNode;
	}

	if (otherNode) 
	{ 
		iterationNode->next = otherNode;
		moptrFirstNode = mergeNode;
		moptrLastNode = other.moptrLastNode;
	}

	other.moptrFirstNode = nullptr;
}
