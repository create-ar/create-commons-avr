#include "stream_reader.h"

StreamReader::StreamReader()
{
    //
}

void StreamReader::set_stream(AvrStream* stream)
{
	stream_ = stream;
}

AvrStream* StreamReader::get_stream()
{
	return stream_;
}

short StreamReader::read_short()
{
	return stream_->read() | (stream_->read() << 8);
}

int StreamReader::read_int()
{
	return stream_->read() | (stream_->read() << 8) | (stream_->read() << 16) | (stream_->read() << 24);
}

char StreamReader::read_byte()
{
	return stream_->read();
}

char* StreamReader::read_bytes()
{
	auto len = read_short();
	auto buffer = new char[len];

	stream_->read(buffer, stream_->get_index(), len);

	return buffer;
}

bool StreamReader::read_bool()
{
	return !(stream_->read() & 0);
}