#include "MemoryStream.h"

#include <string.h>
#include <stdlib.h>

/**
* @brief      Stream implementation completely in memory.
*/
MemoryStream::MemoryStream(const int size) :
	_logger(nullptr),
	_size(size),
	_buffer(nullptr),
	_index(0)
{
	_logger = Log::logger("MemoryStream");
	_buffer = (char*) calloc(_size, sizeof(char));
}

MemoryStream::~MemoryStream()
{
	if (nullptr == _buffer)
	{
		return;
	}
	
	free(_buffer);
}

char MemoryStream::read()
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (_index >= 0 && _index < _size)
	{
		return _buffer[_index++];
	}

	return -1;
}

int MemoryStream::read(
	char* const buffer,
	const int offset,
	const int count)
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > _size)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	// see how many bytes we should read
	int remaining = _size - offset;
	int len = remaining < count
		? remaining
		: count;
	
	if (0 == len)
	{
		return 0;
	}

	memcpy(
		buffer,
		_buffer + offset,
		len);

	return len;
}

bool MemoryStream::write(const char value)
{
	if (nullptr == _buffer)
	{
		return false;
	}

	if (_index < 0 || _index >= _size)
	{
		return false;
	}

	_buffer[_index++] = value;

	return true;
}

int  MemoryStream::write(char* const buffer, const int offset, const int count)
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > _size)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	int remaining = _size - offset;
	int len = remaining < count
		? remaining
		: count;

	if (0 == len)
	{
		return 0;
	}

	memcpy(
		_buffer + offset,
		buffer,
		len);

	return len;
}

int MemoryStream::set(const char value, const int offset, const int count)
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > _size)
	{
		return -1;
	}

	if (count < 0)
	{
		return -1;
	}

	int remaining = _size - offset;
	int len = remaining < count
		? remaining
		: count;

	if (0 == len)
	{
		return 0;
	}

	memset(
		_buffer + offset,
		value,
		count);

	return len;
}

int MemoryStream::seek(const int offset, const int count)
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (offset < 0 || offset > _size)
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
		: calculated > _size
			? _size
			: calculated;

	if (-1 == index)
	{
		return -1;
	}

	_index = index;

	return _index;
}