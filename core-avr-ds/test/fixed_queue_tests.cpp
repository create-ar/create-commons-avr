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

    // add, peek, remove
    {
        auto queue = new FixedQueue<DummyObject>(8);

        auto dummy = new DummyObject();

        REQUIRE(queue->Add(dummy));
        REQUIRE(1 == queue->get_size());

        REQUIRE(queue->Peek() == dummy);
        REQUIRE(1 == queue->get_size());

        REQUIRE(queue->Remove() == dummy);
        REQUIRE(0 == queue->get_size());

        delete dummy;
        delete queue;
    }

    // overfill queue
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

    // over-remove
    {
        const uint32_t queueSize = 8;

        auto queue = new FixedQueue<DummyObject>(queueSize);
        auto dummies = new DummyObject[queueSize];

        for (int i = 0; i < queueSize; i++)
        {
            REQUIRE(queue->Add(&dummies[i]));
        }

        for (int i = 0; i < queueSize; i++)
        {
            REQUIRE(&dummies[i] == queue->Remove());
        }

        REQUIRE(nullptr == queue->Remove());
        
        delete[] dummies;
        delete queue;
    }

    // remove all + re fill
    {
        const uint32_t queueSize = 8;

        auto queue = new FixedQueue<DummyObject>(queueSize);
        auto dummies = new DummyObject[queueSize];

        auto counter = 5;
        while (counter-- > 0)
        {
            for (int i = 0; i < queueSize; i++)
            {
                REQUIRE(queue->Add(&dummies[i]));
            }

            for (int i = 0; i < queueSize; i++)
            {
                REQUIRE(&dummies[i] == queue->Remove());
            }
        }

        delete[] dummies;
        delete queue;
    }

    // remove and add near capacity
    {
        const uint32_t queueSize = 8;

        auto queue = new FixedQueue<DummyObject>(queueSize);
        auto dummies = new DummyObject[32];
        
        // add 7
        auto addCounter = 0;
        auto removeCounter = 0;

        for (int i = 0; i < 7; i++)
        {
            queue->Add(&dummies[addCounter++]);
        }

        // remove 6
        for (int i = 0; i < 6; i++)
        {
            queue->Remove();

            removeCounter++;
        }

        REQUIRE(1 == queue->get_size());

        // add 3 more
        for (int i = 0; i < 3; i++)
        {
            queue->Add(&dummies[addCounter++]);
        }

        // remove remaining 4
        for (int i = 0; i < 4; i++)
        {
            REQUIRE(&dummies[removeCounter++] == queue->Remove());
        }

        REQUIRE(0 == queue->get_size());

        delete[] dummies;
        delete queue;
    }
}