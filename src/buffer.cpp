#include <buffer.h>

template <typename Data>
ListEntry<Data>::ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d)
{
	if (p) p->next = &this;
	if (n) n->previous = &this;
	previous = p;
	next = n;
	data = d;
	if (p)
	{
		index = p->index + 1;
		if (n) n->increaseIndex();
	}
	else index = 0;
}

template <typename Data>
void ListEntry<Data>::increaseIndex()
{
	index++;
	if (next) next->increaseIndex();
}

template <typename Data>
void ListEntry<Data>::decreaseIndex()
{
	index--;
	if (next) next-decreaseIndex();
}

template <typename Data>
int ListEntry<Data>::f(int (*func)(Data))
{
	func(data);
	if (next) next->f(func);
	return 0;
}

template <typename Data>
List<Data>::List()
{
	start = end = 0;
}

template <typename Data>
int List<Data>::insertAfter(ListEntry<Data> *p, Data d)
{
	new ListEntry<Data>(p, p->next, d);
	return 0;
}
