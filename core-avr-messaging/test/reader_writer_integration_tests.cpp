#include <catch.hpp>

#include "memory_stream.h"
#include "stream_reader.h"
#include "stream_writer.h"

TEST_CASE("Reader/Writer Integration", "[StreamReader/StreamWriter]")
{
    const int LEN = 1024;

    auto stream = new MemoryStream(LEN);
    
    auto writer = new StreamWriter();
    writer->set_stream(stream);

    const uint16_t short_value = 173;
    const uint32_t int_value = 32987;
    const char byte_value = 'c';
    const char bytes_value[] = "asdff";
    const bool bool_value = true;

    writer->write_short(short_value);
    writer->write_int(int_value);
    writer->write_byte(byte_value);
    writer->write_bytes((char* const) bytes_value, 5);
    writer->write_bool(bool_value);

    auto reader = new StreamReader();
    stream->seek(0, 0);
    reader->set_stream(stream);
    
    REQUIRE(short_value == reader->read_short());
    REQUIRE(int_value == reader->read_int());
    REQUIRE(byte_value == reader->read_byte());

    auto bytes_read = reader->read_bytes();
    REQUIRE(0 == strcmp(bytes_value, bytes_read));
    delete bytes_read;

    REQUIRE(bool_value == reader->read_bool());

    delete writer;
    delete reader;
    delete stream;
}