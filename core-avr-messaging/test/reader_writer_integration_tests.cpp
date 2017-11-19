#include <catch.hpp>

#include "stream_reader.h"
#include "stream_writer.h"

TEST_CASE("Reader/Writer Integration", "[StreamReader/StreamWriter]")
{
    const int LEN = 1024;

    auto reader = new StreamReader();
    auto writer = new StreamWriter(LEN);

    // plug the writer into the reader
    int len;
    reader->set_buffer(
        writer->get_buffer(&len),
        LEN,
        0);

    SECTION("Short")
	{
        const short value = 173;

        writer->write_short(value);
        
        REQUIRE(value == reader->read_short());
    }

    SECTION("Int")
	{
        const int value = 32987;

        writer->write_int(value);
        
        REQUIRE(value == reader->read_int());
    }

    SECTION("Byte")
	{
        const char value = 'c';

        writer->write_byte(value);
        
        REQUIRE(value == reader->read_byte());
    }

    SECTION("Bytes")
	{
        const char value[] = "asdff";
        
        writer->write_bytes(value, 5);
        
        short len;
        auto read = reader->read_bytes(len);

        REQUIRE(0 == strcmp(value, read));
        REQUIRE(len == 5);

        delete read;
    }

    SECTION("Bool")
	{
        const bool value = true;

        writer->write_bool(value);
        
        REQUIRE(value == reader->read_bool());
    }

    delete writer;
    delete reader;
}