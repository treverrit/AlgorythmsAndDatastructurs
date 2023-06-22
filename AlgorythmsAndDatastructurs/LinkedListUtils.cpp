#include "LinkedListUtils.h"

void LinkedListTest()
{
	CreateLinkedList();
	AppendOnLinkedList();
}

void CreateLinkedList()
{
	LinkedList<int> list{ 2 };
	list.Show();
}

void AppendOnLinkedList()
{
	LinkedList<int> list;
	list.Show();

	for (size_t index = 0; index < 101; ++index)
	{
		list.Append(static_cast<int>(index));
	}

	list.Show();
}
