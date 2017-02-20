#include <catch.hpp>
#include <Log.h>

#include "File.h"
#include "MemoryStreamer.h"

TEST_CASE("File consistency.", "[File]")
{
	int size = 512;

	SECTION("Initialization.")
	{
		Streamer* stream = new MemoryStreamer(size);

		PinConfiguration pins;
		stream->init(pins);

		File* file = new File();

		const int offset = 12;
		const char* nullUri = nullptr;
		const char* uri = "test";

		REQUIRE(!file->init(nullptr, offset, size, uri));
		REQUIRE(!file->init(stream, offset, 0, uri));
		REQUIRE(!file->init(stream, -1, size, uri));
		REQUIRE(!file->init(stream, offset, size, nullUri));

		// should initialize correctly
		REQUIRE(file->init(stream, 0, size, uri));
		delete file;
		
		file = new File();
		REQUIRE(file->load(stream, 0));
		REQUIRE(file->header.contentSize == size);
		REQUIRE(0 == strncmp(
			file->header.uri,
			uri,
			strlen(uri)));

		delete file;
		delete stream;
	}

	SECTION("Data consistency.")
	{
		Streamer* stream = new MemoryStreamer(size);

		PinConfiguration pins;
		stream->init(pins);

		const float values[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f, 10.0f};

		File* file = new File();
		file->init(stream, 0, size, "uri");

		// write values
		int numRecordsToWrite = 10;
		for (int i = 0; i < numRecordsToWrite; i++)
		{
			REQUIRE(file->add(values[i]));
			REQUIRE(file->header.numRecords == i + 1);
		}

		REQUIRE(file->flush());

		// read values
		float* buffer = new float[numRecordsToWrite];
		REQUIRE(-1 == file->values(nullptr, 0, 10));
		REQUIRE(-1 == file->values(buffer, -1, 10));
		REQUIRE(-1 == file->values(buffer, 0, -1));

		// one by one
		float value;
		for (int i = 0; i < numRecordsToWrite; i++)
		{
			REQUIRE(1 == file->values(&value, i, 1));
			REQUIRE(values[i] == value);
		}

		// all at once
		REQUIRE(numRecordsToWrite == file->values(buffer, 0, numRecordsToWrite));
		for (int i = 0; i < numRecordsToWrite; i++)
		{
			REQUIRE(buffer[i] == values[i]);
		}

		delete[] buffer;

		delete file;
	}
}