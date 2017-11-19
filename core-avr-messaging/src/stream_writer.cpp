#include "stream_writer.h"

StreamWriter::StreamWriter(int max_length) : buffer_length_(max_length)
{
	buffer_ = new char[buffer_length_];

	index = 0;
}

StreamWriter::~StreamWriter()
{
	delete[] buffer_;
}

char* StreamWriter::get_buffer(int* len)
{
	*len = buffer_length_;

	return buffer_;
}

const void StreamWriter::write_short(const short value)
{
	ShortUnion converter = ShortUnion();
	converter.short_value = value;

	buffer_[index++] = converter.char_value[0];
	buffer_[index++] = converter.char_value[1];
}

const void StreamWriter::write_int(const int value)
{
	IntUnion converter = IntUnion();
	converter.int_value = value;

	buffer_[index++] = converter.char_value[0];
	buffer_[index++] = converter.char_value[1];
	buffer_[index++] = converter.char_value[2];
	buffer_[index++] = converter.char_value[3];
}

const void StreamWriter::write_byte(const char value)
{
	buffer_[index++] = value;
}

const void StreamWriter::write_bytes(const char* bytes, const short len)
{
	write_short(len);

	for (int i = 0; i < len; i++)
	{
		buffer_[index++] = bytes[i];
	}
}

const void StreamWriter::write_bool(const bool value)
{
	buffer_[index++] = value ? 1 : 0;
}