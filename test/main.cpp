#include <igloo/igloo_alt.h>
#include <buffer.h>
#include <editor.h>
using namespace igloo;

Describe(A_ListEntry)
{
	It(is_inserted_between_two_NULLs)
	{
		ListEntry<void*> *le = new ListEntry<void*>(NULL, NULL, NULL);
		AssertThat(le->previous, Equals((void*) NULL));
		AssertThat(le->next, Equals((void*) NULL));
		AssertThat(le->index, Equals(0));
	}
	It(is_inserted_between_NULL_and_ListEntry)
	{
		ListEntry<void*> *second = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *first = new ListEntry<void*>(NULL, second, NULL);
		AssertThat(first->previous, Equals((void*) NULL));
		AssertThat(first->index, Equals(0));
		AssertThat(first->next, Equals(second));
		AssertThat(second->previous, Equals(first));
		AssertThat(second->index, Equals(1));
		AssertThat(second->next, Equals((void*) NULL));
		ListEntry<void*> *third = new ListEntry<void*>(second, NULL, NULL);
		AssertThat(second->next, Equals(third));
		AssertThat(third->previous, Equals(second));
		AssertThat(third->index, Equals(2));
		AssertThat(third->next, Equals((void*) NULL));
	}
	It(is_inserted_between_two_ListEntrys)
	{
		ListEntry<void*> *first = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *third = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *second = new ListEntry<void*>(first, third, NULL);
		AssertThat(first->previous, Equals((void*) NULL));
		AssertThat(first->index, Equals(0));
		AssertThat(first->next, Equals(second));
		AssertThat(second->previous, Equals(first));
		AssertThat(second->index, Equals(1));
		AssertThat(second->next, Equals(third));
		AssertThat(third->previous, Equals(second));
		AssertThat(third->index, Equals(2));
		AssertThat(third->next, Equals((void*) NULL));
	}
	It(increases_index)
	{
		ListEntry<void*> *first = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *third = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *second = new ListEntry<void*>(first, third, NULL);
		AssertThat(first->index, Equals(0));
		AssertThat(second->index, Equals(1));
		AssertThat(third->index, Equals(2));
	}
};
Describe(A_List)
{
	It(inserts_to_start)
	{
		List<void*> l;
		l.addStart((void*) 1);
		AssertThat(l.start->data, Equals((void*) 1));
		AssertThat(l.start->index, Equals(0));
		AssertThat(l.start, Equals(l.end));
	}
	It(inserts_at_index)
	{
		List<void*> l;
		l.addStart(NULL);
		l.addEnd(NULL);
		l.addIndex(1, (void*) 1);
		AssertThat(l.end->data, Equals((void*) 1));
		l.addIndex(1, (void*) 2);
		AssertThat(l.end->data, Equals((void*) 1));
	}
	It(inserts_to_end)
	{
		List<void*> l;
		l.addEnd((void*) 1);
		AssertThat(l.end->data, Equals((void*) 1));
		AssertThat(l.end->index, Equals(0));
		AssertThat(l.end, Equals(l.start));
		l.addEnd((void*) 2);
		AssertThat(l.end->data, Equals((void*) 2));
		AssertThat(l.end->index, Equals(1));
	}
	It(select_a_ListEntry_by_index)
	{
		List<void*> l;
		l.addEnd((void*) 0);
		l.addEnd((void*) 1);
		l.addEnd((void*) 2);
		AssertThat(l[0].data, Equals((void*) 0));
		AssertThat(l[1].data, Equals((void*) 1));
		AssertThat(l[2].data, Equals((void*) 2));
	}
};

int main(int argc, const char **argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
