#include <igloo/igloo_alt.h>
#include <buffer.h>
#include <editor.h>
using namespace igloo;

Describe(A_ListEntry)
{
	It(is_inserted_between_two_NULLs)
	{
		ListEntry<int> *le = new ListEntry<int>(NULL, NULL, 0);
		AssertThat(le->previous, Equals((void*) NULL));
		AssertThat(le->next, Equals((void*) NULL));
		AssertThat(le->index, Equals(0));
	}
	It(is_inserted_between_NULL_and_ListEntry)
	{
		ListEntry<int> *second = new ListEntry<int>(NULL, NULL, 0);
		ListEntry<int> *first = new ListEntry<int>(NULL, second, 0);
		AssertThat(first->previous, Equals((void*) NULL));
		AssertThat(first->index, Equals(0));
		AssertThat(first->next, Equals(second));
		AssertThat(second->previous, Equals(first));
		AssertThat(second->index, Equals(1));
		AssertThat(second->next, Equals((void*) NULL));
		ListEntry<int> *third = new ListEntry<int>(second, NULL, 0);
		AssertThat(second->next, Equals(third));
		AssertThat(third->previous, Equals(second));
		AssertThat(third->index, Equals(2));
		AssertThat(third->next, Equals((void*) NULL));
	}
	It(is_inserted_between_two_ListEntrys)
	{
		ListEntry<int> *first = new ListEntry<int>(NULL, NULL, 0);
		ListEntry<int> *third = new ListEntry<int>(NULL, NULL, 0);
		ListEntry<int> *second = new ListEntry<int>(first, third, 0);
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
		ListEntry<int> *first = new ListEntry<int>(NULL, NULL, 0);
		ListEntry<int> *third = new ListEntry<int>(NULL, NULL, 0);
		ListEntry<int> *second = new ListEntry<int>(first, third, 0);
		AssertThat(first->index, Equals(0));
		AssertThat(second->index, Equals(1));
		AssertThat(third->index, Equals(2));
	}
};
Describe(A_List)
{
	It(inserts_to_start)
	{
		List<int> l;
		l.addStart(1);
		AssertThat(l.start->data, Equals(1));
		AssertThat(l.start->index, Equals(0));
		AssertThat(l.start, Equals(l.end));
	}
	It(inserts_at_index)
	{
		List<int> l;
		l.addStart(0);
		l.addEnd(0);
		l.addIndex(1, 1);
		AssertThat(l.end->data, Equals(1));
		l.addIndex(1, 2);
		AssertThat(l.end->data, Equals(1));
	}
	It(inserts_to_end)
	{
		List<int> l;
		l.addEnd(1);
		AssertThat(l.end->data, Equals(1));
		AssertThat(l.end->index, Equals(0));
		AssertThat(l.end, Equals(l.start));
		l.addEnd(2);
		AssertThat(l.end->data, Equals(2));
		AssertThat(l.end->index, Equals(1));
	}
	It(select_a_ListEntry_by_index)
	{
		List<int> l;
		l.addEnd(0);
		l.addEnd(1);
		l.addEnd(2);
		AssertThat(l[0].data, Equals(0));
		AssertThat(l[1].data, Equals(1));
		AssertThat(l[2].data, Equals(2));
	}
};

int main(int argc, const char **argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
