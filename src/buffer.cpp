#include <buffer.h>

template <typename Data>
ListEntry<Data>::ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d)
{
	if (p) p->next = this;
	if (n) n->previous = this;
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
int List<Data>::addStart(Data d)
{
        start = new ListEntry<Data>(0, start, d);
        if (!end) end = start;
        return 0;
}

template <typename Data>
int List<Data>::addEnd(Data d)
{
        end = new ListEntry<Data>(end, 0, d);
        if (!start) start = end;
        return 0;
}

template <typename Data>
int List<Data>::f(int (*func)(Data))
{
        start->f(func);
        return 0;
}

Buffer::Buffer()
{
}

int Buffer::addStart(char *str)
{
}

int Buffer::addIndex(char *str)
{
}

int Buffer::addEnd(char *str)
{
}
