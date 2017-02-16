#include <catch.hpp>
#include <string.h>

#include "MemoryStream.h"

TEST_CASE("MemoryStream.", "[MemoryStream]")
{
	const int size = 512;

	SECTION("Bad inputs")
	{
		MemoryStream* stream = new MemoryStream(size);
		char* readBuffer = new char[size];

		SECTION("read()")
		{
			int offset = 12;
			int readSize = 128;

			REQUIRE(0 == stream->read());
			
			REQUIRE(-1 == stream->read(nullptr, offset, readSize));
			
			REQUIRE(-1 == stream->read(readBuffer, -1, readSize));
			REQUIRE(0 == stream->read(readBuffer, size, size));

			REQUIRE(-1 == stream->read(readBuffer, offset, -1));
			REQUIRE(0 == stream->read(readBuffer, offset, 0));

			REQUIRE(readSize == stream->read(readBuffer, offset, readSize));
		}

		SECTION("seek")
		{
			REQUIRE(6 == stream->seek(4, 2));
			REQUIRE(6 == stream->seek(size, 0));
			REQUIRE(6 == stream->seek(6, size));
		}

		SECTION("read()/write()/seek()")
		{
			char write[] = "This is a test.";
			int len = strlen(write);

			stream->seek(4, 0);
			REQUIRE(stream->write(write[7]));
			stream->seek(4, 0);
			REQUIRE(write[7] == stream->read());

			REQUIRE(stream->write(write, 0, strlen(write)));
			REQUIRE(stream->read(readBuffer, 0, strlen(write)));
			REQUIRE(0 == strncmp(readBuffer, write, strlen(write)));
		}
		
		delete[] readBuffer;
		delete stream;
	}
}