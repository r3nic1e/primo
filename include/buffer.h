#ifndef BUFFER_H
#define BUFFER_H

template <typename Data> class ListEntry
{
public:
	ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d);
	int f(int (*func)(Data));
	Data data;
private:
	unsigned index;
protected:
	ListEntry<Data> *next, *previous;
	void increaseIndex();
	void decreaseIndex();
};

template <typename Data> class List
{
public:
	List();
	int insertAfter(ListEntry<Data> *p, Data d);
private:
	ListEntry<Data> *start, *end;
};

class Buffer
{
public:
private:
};

#endif
