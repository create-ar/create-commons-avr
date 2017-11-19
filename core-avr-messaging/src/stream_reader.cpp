#include "stream_reader.h"
#include "converter.h"

StreamReader::StreamReader() : buffer_length_(0), index_(0)
{
    //
}

unsigned char* StreamReader::get_buffer()
{
	return buffer_;
}

void StreamReader::set_buffer(
	unsigned char* buffer,
	int length,
	int index)
{
	buffer_ = buffer;
	buffer_length_ = length;
	index_ = index;
}

int StreamReader::get_index()
{
	return index_;
}

void StreamReader::set_index(int index)
{
	index_ = index;
}

short StreamReader::read_short()
{
	ShortUnion converter;
	converter.char_value[0] = buffer_[index_];
	converter.char_value[1] = buffer_[index_ + 1];

	index_ += 2;

	return converter.short_value;
}

int StreamReader::read_int()
{
	IntUnion converter;
	converter.char_value[0] = buffer_[index_++];
	converter.char_value[1] = buffer_[index_++];
	converter.char_value[2] = buffer_[index_++];
	converter.char_value[3] = buffer_[index_++];

	return converter.int_value;
}

unsigned char StreamReader::read_byte()
{
	return buffer_[index_++];
}

void StreamReader::read_bytes(unsigned char* value, short& len)
{
	len = read_short();
	value = new unsigned char[len];

	for (int i = 0; i < len; i++)
	{
		value[i] = buffer_[index_ + i];
	}

	index_ += len;
}

bool StreamReader::read_bool()
{
	return !(buffer_[index_++] & 0);
}