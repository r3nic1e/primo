#ifndef BUFFER_H
#define BUFFER_H

template <typename Data> class ListEntry
{
public:
	ListEntry(ListEntry<Data> *p, ListEntry<Data> *n, Data d);
	int f(int (*func)(Data));
	Data data;
	ListEntry<Data> *next, *previous;
private:
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
	int f(int (*func)(Data));
	Data operator [](unsigned i);
private:
	ListEntry<Data> *start, *end;
};

class Buffer
{
public:
	Buffer();
	int addStart(char *str);
	int addIndex(unsigned y, char *str);
	int addIndex(unsigned y, unsigned x, char c);
	int addEnd(char *str);
private:
	List<char*> lines;
};

#endif
