#include <catch.hpp>
#include <string.h>
#include <PinConfiguration.h>

#include "MemoryStreamer.h"

TEST_CASE("MemoryStreamer.", "[MemoryStream]")
{
	const int size = 512;

	SECTION("init()")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		char* readBuffer = new char[size];

		PinConfiguration pins;
		REQUIRE(stream->init(pins));
		
		delete[] readBuffer;
		delete stream;
	}

	SECTION("read()")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		char* readBuffer = new char[size];

		REQUIRE(-1 == stream->read());
		
		PinConfiguration pins;
		stream->init(pins);

		int offset = 12;
		int readSize = 128;

		// default data is zeroed out
		REQUIRE(0 == stream->read());
		
		// invalid inputs
		REQUIRE(-1 == stream->read(nullptr, offset, readSize));
		REQUIRE(-1 == stream->read(readBuffer, -1, readSize));
		REQUIRE(-1 == stream->read(readBuffer, offset, -1));

		// clamped inputs
		REQUIRE(0 == stream->read(readBuffer, size, size));
		REQUIRE(0 == stream->read(readBuffer, offset, 0));

		REQUIRE(readSize == stream->read(readBuffer, offset, readSize));

		delete readBuffer;
		delete stream;
	}

	SECTION("seek()")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		char* readBuffer = new char[size];

		REQUIRE(-1 == stream->seek(0, 1));

		PinConfiguration pins;
		stream->init(pins);

		REQUIRE(-1 == stream->seek(-1, 2));
		REQUIRE(-1 == stream->seek(0, -1));

		REQUIRE(0 == stream->seek(0, 0));
		REQUIRE(size == stream->seek(size, size));

		REQUIRE(6 == stream->seek(4, 2));
		REQUIRE(size == stream->seek(size, 0));
		REQUIRE(size == stream->seek(6, size));

		delete[] readBuffer;
		delete stream;
	}

	SECTION("write()")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		char* readBuffer = new char[size];
		
		REQUIRE(!stream->write('a'));

		PinConfiguration pins;
		REQUIRE(stream->init(pins));

		REQUIRE(stream->write('a'));

		delete[] readBuffer;
		delete stream;
	}

	SECTION("read()/write()/seek() char")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		char* readBuffer = new char[size];

		char write[] = "This is a test.";
		int len = strlen(write);

		REQUIRE(-1 == stream->write(write, 0, len));
		
		PinConfiguration pins;
		stream->init(pins);

		REQUIRE(stream->write(write[7]));
		stream->seek(0, 0);
		REQUIRE(write[7] == stream->read());

		REQUIRE(stream->write(write, 0, len));
		REQUIRE(stream->read(readBuffer, 0, len));
		REQUIRE(0 == strncmp(readBuffer, write, len));
		
		delete[] readBuffer;
		delete stream;
	}

	SECTION("set()")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);		
		PinConfiguration pins;
		stream->init(pins);

		char readBuffer[size];
		char writeBuffer[size];
		
		memset(writeBuffer, 'a', size);
		REQUIRE(size == stream->write((char* const) writeBuffer, 0, size));
		REQUIRE(size == stream->read(readBuffer, 0, size));
		REQUIRE(0 == strncmp(readBuffer, writeBuffer, size));

		memset(writeBuffer, '\0', size);
		REQUIRE(size == stream->set('\0', 0, size));
		REQUIRE(size == stream->read(readBuffer, 0, size));
		REQUIRE(0 == strncmp(readBuffer, writeBuffer, size));

		delete stream;
	}
}