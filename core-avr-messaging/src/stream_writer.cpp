#include "stream_writer.h"

StreamWriter::StreamWriter()
{
	
}

void StreamWriter::set_stream(AvrStream* stream)
{
	stream_ = stream;
}

AvrStream* StreamWriter::get_stream()
{
	return stream_;
}

const void StreamWriter::write_short(const short value)
{
	stream_->write(value & 0xFF);
	stream_->write((value >> 8) & 0xFF);
}

const void StreamWriter::write_int(const int value)
{
	stream_->write(value & 0xFF);
	stream_->write((value >> 8) & 0xFF);
	stream_->write((value >> 16) & 0xFF);
	stream_->write((value >> 24) & 0xFF);
}

const void StreamWriter::write_byte(const unsigned char value)
{
	stream_->write(value);
}

const void StreamWriter::write_bytes(unsigned char* bytes, const int16_t len)
{
	write_short(len);
	
	stream_->write(bytes, 0, len);
}

const void StreamWriter::write_bool(const bool value)
{
	write_int(value ? 1 : 0);
}