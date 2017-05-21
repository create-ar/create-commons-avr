#include "memory_stream.h"

#include <string.h>
#include <stdlib.h>

/**
* @brief      Stream implementation completely in memory.
*/
MemoryStream::MemoryStream(const int size) :
	logger_(nullptr),
	size_(size),
	buffer_(nullptr),
	index_(0)
{
	logger_ = Log::logger("MemoryStream");
	buffer_ = (char*) calloc(size_, sizeof(char));
}

MemoryStream::~MemoryStream()
{
	if (nullptr == buffer_)
	{
		return;
	}
	
	free(buffer_);
}

char MemoryStream::read()
{
	if (nullptr == buffer_)
	{
		return -1;
	}

	if (index_ >= 0 && index_ < size_)
	{
		return buffer_[index_++];
	}

	return -1;
}

int MemoryStream::read(
	char* const buffer,
	const int offset,
	const int count)
{
	if (nullptr == buffer_)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > size_)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	// see how many bytes we should read
	int remaining = size_ - offset;
	int len = remaining < count
		? remaining
		: count;
	
	if (0 == len)
	{
		return 0;
	}

	memcpy(
		buffer,
		buffer_ + offset,
		len);

	return len;
}

bool MemoryStream::write(const char value)
{
	if (nullptr == buffer_)
	{
		return false;
	}

	if (index_ < 0 || index_ >= size_)
	{
		return false;
	}

	buffer_[index_++] = value;

	return true;
}

int  MemoryStream::write(char* const buffer, const int offset, const int count)
{
	if (nullptr == buffer_)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > size_)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	int remaining = size_ - offset;
	int len = remaining < count
		? remaining
		: count;

	if (0 == len)
	{
		return 0;
	}

	memcpy(
		buffer_ + offset,
		buffer,
		len);

	return len;
}

int MemoryStream::set(const char value, const int offset, const int count)
{
	if (nullptr == buffer_)
	{
		return -1;
	}

	if (offset < 0 || offset > size_)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	int remaining = size_ - offset;
	int len = remaining < count
		? remaining
		: count;

	if (0 == len)
	{
		return 0;
	}

	memset(
		buffer_ + offset,
		value,
		count);

	return len;
}

int MemoryStream::seek(const int offset, const int count)
{
	if (nullptr == buffer_)
	{
		return -1;
	}

	if (offset < 0 || offset > size_)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	int calculated = offset + count;
	int index = calculated < 0
		? 0
		: calculated > size_
			? size_
			: calculated;

	if (-1 == index)
	{
		return -1;
	}

	index_ = index;

	return index_;
}