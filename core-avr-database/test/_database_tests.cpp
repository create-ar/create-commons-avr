#include <catch.hpp>
#include <log.h>

#include "database.h"
#include "memory_stream.h"
#include "avr_clock.h"
#include "standard_clock.hpp"

TEST_CASE("Database consistency.", "[Database]")
{
	int size = 512;
	const int offset = 12;
	const char* nullUri = nullptr;
	const char* uri = "test";
	const char valuesPerRecord = 3;

	SECTION("Initialization.")
	{
		AvrStream* stream = new MemoryStream(size);
		AvrClock* clock = new StandardClock();
		Database* database = new Database(clock);

		REQUIRE(!database->init(nullptr, offset, size, valuesPerRecord, uri));
		REQUIRE(!database->init(stream, offset, 0, valuesPerRecord, uri));
		REQUIRE(!database->init(stream, -1, size, valuesPerRecord, uri));
		REQUIRE(!database->init(stream, offset, size, 0, uri));
		REQUIRE(!database->init(
			stream,
			offset,
			size,
			valuesPerRecord,
			nullUri));

		// should initialize correctly
		REQUIRE(database->init(stream, 0, size, valuesPerRecord, uri));
		delete database;
		
		database = new Database(clock);
		REQUIRE(database->load(stream, 0));
		REQUIRE(database->header.contentSize == size);
		REQUIRE(0 == strncmp(
			database->header.uri,
			uri,
			strlen(uri)));

		delete database;
		delete clock;
		delete stream;
	}

	SECTION("Record format")
	{
		AvrClock* clock = new StandardClock();
		AvrStream* stream = new MemoryStream(size);
		Database* database = new Database(clock);
		database->init(stream, offset, size, valuesPerRecord, uri);

		// create some values
		float values[valuesPerRecord];
		for (int i = 0; i < valuesPerRecord; i++)
		{
			values[i] = i;
		}
		// 0, 1, 2, ...
		
		REQUIRE(database->add(values));

		// read a record
		char readValues[(valuesPerRecord + 1) * 4];

		REQUIRE(-1 == database->dump(nullptr, 0, 1));
		REQUIRE(-1 == database->dump(readValues, -1, 1));
		REQUIRE(-1 == database->dump(readValues, 1, 1));

		REQUIRE(1 == database->dump(readValues, 0, 1));

		// verify format
		REQUIRE(0 == memcmp(values, readValues + 4, 4 * valuesPerRecord));

		delete database;
		delete stream;
		delete clock;
	}

	SECTION("dump() full records")
	{
		const int numRecords = 10;
		const int numTotalValues = numRecords * valuesPerRecord;
		
		float allValues[numTotalValues];
		for (int i = 0; i < numTotalValues; i++)
		{
			allValues[i] = i;
		}

		AvrClock* clock = new StandardClock();
		AvrStream* stream = new MemoryStream(size);
		Database* database = new Database(clock);
		database->init(stream, 0, size, (char) valuesPerRecord, "uri");

		// write values
		for (int i = 0; i < numRecords; i++)
		{
			REQUIRE(database->add(allValues + valuesPerRecord * i));
			REQUIRE(database->header.numRecords == i + 1);
		}

		REQUIRE(database->flush());

		const int numTotalReadBytes = (numTotalValues + numRecords) * 4;
		char readBuffer[numTotalReadBytes];

		// try invalid parameters
		REQUIRE(-1 == database->dump(nullptr, 0, 10));
		REQUIRE(-1 == database->dump(readBuffer, -1, 10));
		REQUIRE(-1 == database->dump(readBuffer, 0, -1));

		// read all values at once
		// [timestamp][value]...[value]
		REQUIRE(numRecords == database->dump(
			readBuffer,
			0,
			numRecords));
		for (int i = 0; i < numRecords; i++)
		{
			// calculate index to record
			int readBufferIndex = i * (1 + valuesPerRecord) * 4;

			// calculate index into allvalues
			int valuesIndex = i * valuesPerRecord;

			REQUIRE(0 == memcmp(
				readBuffer + readBufferIndex + 4,
				allValues + valuesIndex,
				valuesPerRecord * 4));
		}

		delete database;
		delete stream;
		delete clock;
	}
}