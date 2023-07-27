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
private:
	Node* moptrFirstNode;
	Node* moptrLastNode;
};

template<typename Type>
inline LinkedList<Type>::LinkedList() noexcept
	:moptrFirstNode(nullptr)
	,moptrLastNode(nullptr)
{}

template<typename Type>
inline LinkedList<Type>::LinkedList(Type data) noexcept
	:moptrFirstNode(new Node)
{
	moptrFirstNode->data = data;
	moptrFirstNode->next = nullptr;
	moptrLastNode = moptrFirstNode;
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
