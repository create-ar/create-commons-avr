#include <catch.hpp>

#include "linked_list.h"

static int ids = 0;

class DummyObject
{
public:
	int id;

	DummyObject()
	{
		id = ids++;
	}
};

TEST_CASE("LinkedList<T>.", "[LinkedList]")
{
	LinkedList<DummyObject>* list = new LinkedList<DummyObject>();

	// add/contains/remove
	{
		REQUIRE(list->count() == 0);

		DummyObject* dummy = new DummyObject;
		list->add(dummy);

		REQUIRE(list->count() == 1);
		REQUIRE(list->contains(dummy));
		REQUIRE(list->remove(dummy));
		REQUIRE(!list->contains(dummy));
		REQUIRE(list->count() == 0);
		REQUIRE(!list->remove(dummy));

		delete dummy;
	}

	// clear
	{
		int len = 5;
		DummyObject* dummies[len];
		for (int i = 0; i < len; i++)
		{
			dummies[i] = new DummyObject();
			list->add(dummies[i]);
		}

		REQUIRE(list->count() == len);
		list->clear();
		REQUIRE(list->count() == 0);

		for (int i = 0; i < len; i++)
		{
			delete dummies[i];
		}
	}

	// iteration
	{
		int len = 5;
		DummyObject* dummies[len];
		for (int i = 0; i < len; i++)
		{
			dummies[i] = new DummyObject();
			list->add(dummies[i]);
		}

		auto counter = 0;
		auto it = list->it();
		
		while (it->moveNext())
		{
			REQUIRE(it->current() == dummies[counter++]);
		}

		for (int i = 0; i < len; i++)
		{
			delete dummies[i];
		}
	}

	delete list;
}