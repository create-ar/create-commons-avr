#include <catch.hpp>

#include "stream_writer.h"

TEST_CASE("StreamWriter", "[StreamWriter]")
{
    const int LEN = 1024;

    auto writer = new StreamWriter(LEN);

    SECTION("")
	{
        
    }

    delete writer;
}