#include <buffer.h>
#include <defines.h>

template <typename Data>
ListEntry<Data>::ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d)
{
	if (p) p->next = this;
	if (n) n->previous = this;
	previous = p;
	next = n;
	data = d;
	if (p) index = p->index + 1;
	else index = 0;
	if (n) n->increaseIndex();
}

template <typename Data>
void ListEntry<Data>::increaseIndex()
{
	if (index) index++;
	else index = previous->index + 1;
	if (next) next->increaseIndex();
}

template <typename Data>
void ListEntry<Data>::decreaseIndex()
{
	index--;
	if (next) next->decreaseIndex();
}

template <typename Data>
int ListEntry<Data>::invoke(int (*func)(ListEntry<Data>, void*), void* p)
{
	func(*this, p);
	if (next) next->invoke(func, p);
	return 0;
}

template <typename Data>
List<Data>::List()
{
	start = end = NULL;
}

template <typename Data>
int List<Data>::addStart(Data d)
{
	start = new ListEntry<Data>(NULL, start, d);
	if (!end) end = start;
	return 0;
}

template <typename Data>
int List<Data>::addIndex(unsigned index, Data d)
{
	if (!index) return addStart(d);
	ListEntry<Data> *temp = start;
	for (unsigned i = index; i > 0; i--) temp = temp->next;
	if (temp == end) return addEnd(d);
	new ListEntry<Data>(temp, temp->next, d);
	return 0;
}

template <typename Data>
int List<Data>::addEnd(Data d)
{
	ListEntry<Data> *temp = new ListEntry<Data>(end, NULL, d);
	end = temp;
	if (!start) start = end;
	return 0;
}

template <typename Data>
int List<Data>::invoke(int (*func)(ListEntry<Data>, void*), void* p)
{
	start->invoke(func, p);
	return 0;
}

template <typename Data>
ListEntry<Data> List<Data>::operator [](unsigned i)
{
	ListEntry<Data> *temp = start;
	for (unsigned t = 0; t < i; t++)
		temp = temp->next;
	return *temp;
}

Buffer::Buffer()
{
}

int Buffer::addStart(char *str)
{
	return lines.addStart(str);
}

int Buffer::addIndex(unsigned y, char *str)
{
	return lines.addIndex(y, str);
}

int Buffer::addIndex(unsigned y, unsigned x, char c)
{
	lines[y].data[x] = c;
	return 0;
}

int Buffer::addEnd(char *str)
{
	return lines.addEnd(str);
}

int Buffer::invoke(int (*func)(ListEntry<char*>, void*), void* p)
{
	return lines.invoke(func, p);
}

template class ListEntry<char*>;
template class ListEntry<void*>;
template class List<char*>;
template class List<void*>;
