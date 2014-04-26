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
	}
	It(is_inserted_between_NULL_and_ListEntry)
	{
		ListEntry<void*> *first = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *second = new ListEntry<void*>(first, NULL, NULL);
		AssertThat(first->previous, Equals((void*) NULL));
		AssertThat(first->next, Equals(second));
		AssertThat(second->previous, Equals(first));
		AssertThat(second->next, Equals((void*) NULL));
	}
	It(is_inserted_between_two_ListEntrys)
	{
		ListEntry<void*> *first = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *third = new ListEntry<void*>(NULL, NULL, NULL);
		ListEntry<void*> *second = new ListEntry<void*>(first, third, NULL);
		AssertThat(first->previous, Equals((void*) NULL));
		AssertThat(first->next, Equals(second));
		AssertThat(second->previous, Equals(first));
		AssertThat(second->next, Equals(third));
		AssertThat(third->previous, Equals(second));
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

int main(int argc, const char **argv)
{
	return TestRunner::RunAllTests(argc, argv);
}
