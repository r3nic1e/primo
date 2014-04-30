#include <buffer.h>
#include <defines.h>
#include <string>

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
int ListEntry<Data>::invoke(int (*func)(ListEntry<Data>, void*), unsigned count, void* p)
{
	if (!count) return 1;
	func(*this, p);
	if (next) next->invoke(func, count - 1, p);
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
int List<Data>::invoke(int (*func)(ListEntry<Data>, void*), unsigned st, void* p)
{
	ListEntry<Data> *s = (*this)[st];
	s->invoke(func, p);
	return 0;
}

template <typename Data>
int List<Data>::invoke(int (*func)(ListEntry<Data>, void*), unsigned st, unsigned count, void* p)
{
	ListEntry<Data> *s = (*this)[st];
	s->invoke(func, count, p);
	return 0;
}

template <typename Data>
ListEntry<Data>* List<Data>::operator [](unsigned i)
{
	ListEntry<Data> *temp = start;
	for (unsigned t = 0; t < i; t++)
		temp = temp->next;
	return temp;
}

Buffer::Buffer()
{
}

int Buffer::addStart(std::string str)
{
	return lines.addStart(str);
}

int Buffer::addIndex(unsigned y, std::string str)
{
	return lines.addIndex(y, str);
}

int Buffer::addEnd(std::string str)
{
	return lines.addEnd(str);
}

int Buffer::invoke(int (*func)(ListEntry<std::string>, void*), void* p)
{
	return lines.invoke(func, p);
}

int Buffer::invoke(int (*func)(ListEntry<std::string>, void*), unsigned start, void* p)
{
	return lines.invoke(func, start, p);
}

int Buffer::invoke(int (*func)(ListEntry<std::string>, void*), unsigned start, unsigned count, void* p)
{
	return lines.invoke(func, start, count, p);
}

template class ListEntry<std::string>;
template class ListEntry<int>;
template class List<std::string>;
template class List<int>;
