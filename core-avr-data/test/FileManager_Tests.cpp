#include <catch.hpp>

#include <stdlib.h>
#include <string.h>

#include "File.h"
#include "FileManager.h"
#include "MemoryStreamer.h"

TEST_CASE("FileManager usage.", "[FileManager]")
{
	const int size = 4096;
	const int filesize = 128;

	SECTION("Initialization.")
	{
		const short version = 23;
		const short numFiles = 12;
		const int usedBytes = 1025;
		const int totalBytes = 4096;

		FileManagerConfig config;
		config.totalBytes = totalBytes;

		MemoryStreamer* stream = new MemoryStreamer(totalBytes);
		PinConfiguration pins;
		stream->init(pins);

		FileManager* files = new FileManager(stream);
		REQUIRE(files->init(config));
		delete files;

		files = new FileManager(stream);
		REQUIRE(files->load(config));

		delete files;
		delete stream;
	}

	SECTION("Create")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		PinConfiguration pins;
		stream->init(pins);

		FileManager* files = new FileManager(stream);

		FileManagerConfig config;
		REQUIRE(files->init(config));

		const char* uri = "/records/moisturesensor";
		REQUIRE(nullptr == files->create(nullptr, filesize));
		REQUIRE(nullptr == files->create(uri, 0));
		REQUIRE(nullptr == files->create(uri, -1));
		REQUIRE(nullptr == files->create(uri, size + 1));

		File* file = files->create(uri, filesize);
		REQUIRE(nullptr != file);
		
		delete files;
		delete stream;
	}

	SECTION("Get/Set")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		PinConfiguration pins;
		stream->init(pins);

		FileManager* files = new FileManager(stream);

		FileManagerConfig config;
		REQUIRE(files->init(config));

		const char* uri = "/records/moisturesensor";
		File* file = files->create(uri, filesize);

		REQUIRE(nullptr == files->get(nullptr));
		REQUIRE(nullptr == files->get("other"));
		REQUIRE(file == files->get(uri));
		REQUIRE(files->set(file));
		
		delete files;
		delete stream;
	}

	SECTION("Get many")
	{
		MemoryStreamer* stream = new MemoryStreamer(size);
		PinConfiguration pins;
		stream->init(pins);

		FileManager* files = new FileManager(stream);

		FileManagerConfig config;
		REQUIRE(files->init(config));

		// create many files
		const int numFiles = 10;
		const int fileSize = 512;
		File* tempFiles[numFiles];

		char* uriBuffer;

		for (int i = 0; i < numFiles; i++)
		{
			uriBuffer = (char*) calloc(16, 0);
			sprintf(uriBuffer, "/db/sensor/%i", i);

			tempFiles[i] = files->create((const char*) uriBuffer, fileSize);

			free(uriBuffer);
		}
		
		for (int i = 0; i < numFiles; i++)
		{
			uriBuffer = (char*) calloc(16, 0);
			sprintf(uriBuffer, "/db/sensor/%i", i);

			REQUIRE(tempFiles[i] == files->get((const char*) uriBuffer));

			free(uriBuffer);
		}

		delete files;
		delete stream;
	}
}