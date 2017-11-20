#include "memory_stream.h"

#include <string.h>
#include <stdlib.h>

/**
* @brief      Stream implementation completely in memory.
*/
MemoryStream::MemoryStream(const int32_t size) :
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

int32_t MemoryStream::get_index()
{
	return index_;
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

int32_t MemoryStream::read(
	unsigned char* const buffer,
	const int32_t offset,
	const int32_t count)
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
	int32_t remaining = size_ - offset;
	int32_t len = remaining < count
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

bool MemoryStream::write(const unsigned char value)
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

int32_t MemoryStream::write(unsigned char* const buffer, const int32_t offset, const int32_t count)
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

	int32_t remaining = size_ - offset;
	int32_t len = remaining < count
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

int32_t MemoryStream::set(const unsigned char value, const int32_t offset, const int32_t count)
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

	int32_t remaining = size_ - offset;
	int32_t len = remaining < count
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

int32_t MemoryStream::seek(const int32_t offset, const int32_t count)
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

	int32_t calculated = offset + count;
	int32_t index = calculated < 0
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