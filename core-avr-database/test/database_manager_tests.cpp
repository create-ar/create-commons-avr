#include <catch.hpp>

#include <stdlib.h>
#include <string.h>

#include "database.h"
#include "database_manager.h"
#include "memory_stream.h"
#include "standard_clock.hpp"

TEST_CASE("DatabaseManager usage.", "[DatabaseManager]")
{
	const int size = 4096;
	const int filesize = 128;
	const int valuesPerRecord = 3;

	SECTION("Initialization.")
	{
		const short version = 23;
		const short numDatabases = 12;
		const int usedBytes = 1025;
		const int totalBytes = 4096;

		DatabaseManagerConfig config;
		config.totalBytes = totalBytes;

		AvrClock* clock = new StandardClock();
		MemoryStream* stream = new MemoryStream(totalBytes);
		DatabaseManager* files = new DatabaseManager(clock, stream);
		REQUIRE(files->init(config));
		delete files;

		files = new DatabaseManager(clock, stream);
		REQUIRE(files->load(config));

		delete files;
		delete stream;
		delete clock;
	}

	SECTION("Create")
	{
		AvrClock* clock = new StandardClock();
		MemoryStream* stream = new MemoryStream(size);
		DatabaseManager* files = new DatabaseManager(clock, stream);

		DatabaseManagerConfig config;
		config.totalBytes = size;
		REQUIRE(files->init(config));

		const char* uri = "/records/moisturesensor";
		REQUIRE(nullptr == files->create(nullptr, filesize, valuesPerRecord));
		REQUIRE(nullptr == files->create(uri, 0, valuesPerRecord));
		REQUIRE(nullptr == files->create(uri, -1, valuesPerRecord));
		REQUIRE(nullptr == files->create(uri, filesize, 0));
		REQUIRE(nullptr == files->create(uri, size + 1, valuesPerRecord));

		Database* file = files->create(uri, filesize, valuesPerRecord);
		REQUIRE(nullptr != file);
		
		delete files;
		delete stream;
		delete clock;
	}

	SECTION("Get()")
	{
		AvrClock* clock = new StandardClock();
		MemoryStream* stream = new MemoryStream(size);
		DatabaseManager* files = new DatabaseManager(clock, stream);

		DatabaseManagerConfig config;
		REQUIRE(files->init(config));

		const char* uri = "/records/moisturesensor";
		Database* file = files->create(uri, filesize, valuesPerRecord);
		delete file;

		REQUIRE(nullptr == files->get(nullptr));
		REQUIRE(nullptr == files->get("other"));

		file = files->get(uri);
		REQUIRE(nullptr != file);
		delete file;
		
		delete files;
		delete stream;
		delete clock;
	}

	SECTION("Get many")
	{
		AvrClock* clock = new StandardClock();
		MemoryStream* stream = new MemoryStream(size);
		DatabaseManager* files = new DatabaseManager(clock, stream);

		DatabaseManagerConfig config;
		config.totalBytes = size;
		REQUIRE(files->init(config));

		// create many files
		const int numDatabases = 10;
		const int fileSize = 128;
		char* uriBuffer;

		for (int i = 0; i < numDatabases; i++)
		{
			uriBuffer = (char*) calloc(16, 0);
			sprintf(uriBuffer, "/db/sensor/%i", i);

			Database* file = files->create(
				(const char*) uriBuffer,
				fileSize,
				valuesPerRecord);

			REQUIRE(nullptr != file);

			delete file;

			free(uriBuffer);
		}
		
		for (int i = 0; i < numDatabases; i++)
		{
			uriBuffer = (char*) calloc(16, 0);
			sprintf(uriBuffer, "/db/sensor/%i", i);

			Database* file = files->get((const char*) uriBuffer);

			REQUIRE(nullptr != file);

			delete file;

			free(uriBuffer);
		}

		delete files;
		delete stream;
		delete clock;
	}
}