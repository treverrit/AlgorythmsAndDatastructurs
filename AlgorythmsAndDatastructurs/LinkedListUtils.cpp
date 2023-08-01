#include "LinkedListUtils.h"

void LinkedListTest()
{
	CreateLinkedList();
	AppendOnLinkedList();
	MakeLinkedListUnique();
	ReverseLinkedList();
	ConcatLinkedLists();
	MergeLinkedList();
	CheckLinkedListForLoop();
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

void MakeLinkedListUnique()
{
	LinkedList<int>list{};
	list.Append(0);
	list.Append(0);
	list.Append(0);

	for (size_t index = 0; index < 11; index++)
	{
		list.Append(static_cast<int>(index));
	}

	list.Append(10);
	list.Append(10);
	list.Append(10);

	list.Show();

	list.Makeunique();

	list.Show();
}

void ReverseLinkedList()
{
	LinkedList<int>list{};

	for (size_t index = 0; index < 11; ++index)
	{
		list.Append(static_cast<int>(index));
	}

	list.Show();

	list.Reverse();

	list.Show();
}

void ConcatLinkedLists()
{
	LinkedList<int>list{};
	LinkedList<int>list2{};

	for (size_t index = 0; index < 11; ++index)
	{
		list.Append(static_cast<int>(index) + 2);
		list2.Append(static_cast<int>(index) * 2);
	}

	list.Show();
	list2.Show();

	list.Concat(list2);

	list.Show();
}

void MergeLinkedList()
{
	LinkedList<int>list{};
	LinkedList<int>list2{};

	for (size_t index = 0; index < 11; ++index)
	{
		list.Append(static_cast<int>(index) + 2);
		list2.Append(static_cast<int>(index) * 2);
	}

	list.Show();
	list2.Show();

	list.Merge(list2);

	list.Show();

	std::cout << list.First() << std::endl;
	std::cout << list.Last() << std::endl;
}

void CheckLinkedListForLoop()
{
	LinkedList<int>list{};

	for (size_t index = 0; index <= 20; ++index)
	{
		list.Append(static_cast<int>(index));
	}

	LinkedList<int>::Node* t1 = list.FirstNode()->next->next->next;
	LinkedList<int>::Node* t2 = list.LastNode();
	t2->next = t1;

	std::cout << ((list.HasLoop()) ? "List has a loop" : "List has not a loop") << std::endl;

	t2->next = nullptr;

	std::cout << ((list.HasLoop()) ? "List has a loop" : "List has not a loop") << std::endl;
}
