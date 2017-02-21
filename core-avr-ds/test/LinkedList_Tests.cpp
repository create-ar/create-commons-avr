#include <catch.hpp>

#include "LinkedList.h"

static int ids = 0;

class DummyObject
{
public:
	int id;

	DummyObject()
	{
		id = ids++;
	}
}

TEST_SUITE("LinkedList<T>.", "[LinkedList]")
{
	
}