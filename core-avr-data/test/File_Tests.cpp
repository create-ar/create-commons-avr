#include <catch.hpp>

#include "File.h"
#include "MemoryStream.h"

TEST_CASE("File consistency.", "[File]")
{
	int size = 512;
	int offset = 12;

	SECTION("Initialization.")
	{
		MemoryStream* stream = new MemoryStream(size);
		File* file = new File();

		SECTION("Bad parameters.")
		{
			REQUIRE(!file->init(nullptr, offset, size));
			REQUIRE(!file->init(stream, offset, 0));
			REQUIRE(!file->init(stream, -1, size));
		}

		// should initialize correctly
		REQUIRE(file->init(stream, 0, size));
		delete file;
		file = new File();
		REQUIRE(file->load(stream, 0));
		REQUIRE(file->size() == size);
		REQUIRE(file->header.size == size);

		delete file;
		delete stream;
	}

	SECTION("Data consistency.")
	{
		Stream* stream = new MemoryStream(size);
		File* file = new File();
		

		delete file;
		delete stream;
	}
}