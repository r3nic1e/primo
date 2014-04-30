#ifndef BUFFER_H
#define BUFFER_H

#include <string>

template <typename Data> class ListEntry
{
public:
	ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d);
	int invoke(int (*func)(ListEntry<Data>, void*), void* p);
	int invoke(int (*func)(ListEntry<Data>, void*), unsigned count, void* p);
	Data data;
	ListEntry<Data> *next, *previous;
	unsigned index;
protected:
	void increaseIndex();
	void decreaseIndex();
};

template <typename Data> class List
{
public:
	List();
	int addStart(Data d);
	int addIndex(unsigned index, Data d);
	int addEnd(Data d);
	int invoke(int (*func)(ListEntry<Data>, void*), void* p);
	int invoke(int (*func)(ListEntry<Data>, void*), unsigned start, void* p);
	int invoke(int (*func)(ListEntry<Data>, void*), unsigned start, unsigned count, void* p);
	ListEntry<Data>* operator [](unsigned i);
	ListEntry<Data> *start, *end;
};

class Buffer
{
public:
	Buffer();
	int addStart(std::string str);
	int addIndex(unsigned y, std::string str);
	int addEnd(std::string str);
	int invoke(int (*func)(ListEntry<std::string>, void*), void* p);
	int invoke(int (*func)(ListEntry<std::string>, void*), unsigned start, void* p);
	int invoke(int (*func)(ListEntry<std::string>, void*), unsigned start, unsigned count, void* p);
	List<std::string> lines;
};

#endif
