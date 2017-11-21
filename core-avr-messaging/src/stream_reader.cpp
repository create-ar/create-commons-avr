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

int16_t StreamReader::read_short()
{
	return stream_->read() | (stream_->read() << 8);
}

int32_t StreamReader::read_int()
{
	return stream_->read() | (stream_->read() << 8) | (stream_->read() << 16) | (stream_->read() << 24);
}

unsigned char StreamReader::read_byte()
{
	return stream_->read();
}

unsigned char* StreamReader::read_bytes()
{
	auto len = read_short();
	auto buffer = new unsigned char[len];

	stream_->read(buffer, stream_->get_index(), len);

	return buffer;
}

bool StreamReader::read_bool()
{
	return !(stream_->read() & 0);
}