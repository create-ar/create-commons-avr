#include <catch.hpp>

#include "fixed_queue.h"

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

TEST_CASE("FixedQueue<T>.", "[FixedQueue]")
{
    // size
    {
        auto queue = new FixedQueue<DummyObject>(8);

        REQUIRE(0 == queue->get_size());
        REQUIRE(8 == queue->get_capacity());

        delete queue;
    }

    // add, peek, poll
    {
        auto queue = new FixedQueue<DummyObject>(8);

        auto dummy = new DummyObject();

        REQUIRE(queue->Add(dummy));
        REQUIRE(1 == queue->get_size());

        REQUIRE(queue->Peek() == dummy);
        REQUIRE(1 == queue->get_size());

        REQUIRE(queue->Poll() == dummy);
        REQUIRE(0 == queue->get_size());

        delete dummy;
        delete queue;
    }

    // overrfill queue
    {
        const uint32_t queueSize = 8;
        const uint32_t dummyLen = 12;

        auto queue = new FixedQueue<DummyObject>(queueSize);
        auto dummies = new DummyObject[dummyLen];

        for (int i = 0; i < queueSize; i++)
        {
            REQUIRE(queue->Add(&dummies[i]));
        }

        for (int i = queueSize; i < dummyLen; i++)
        {
            REQUIRE(!queue->Add(&dummies[i]));
        }

        delete[] dummies;
        delete queue;
    }
}