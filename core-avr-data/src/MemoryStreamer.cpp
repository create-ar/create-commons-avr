#include "MemoryStreamer.h"

#include <stdlib.h>

/**
* @brief      Stream implementation completely in memory.
*/

MemoryStreamer::MemoryStreamer(const int size) : _size(size)
{
	_logger = Log::logger("MemoryStreamer");
	_index = 0;
}

MemoryStreamer::~MemoryStreamer()
{
	if (nullptr == _buffer)
	{
		return;
	}
	
	free(_buffer);
}

bool MemoryStreamer::init(PinConfiguration pins)
{
	// already initialized
	if (nullptr != _buffer)
	{
		_logger->warn("MemoryStreamer already initialized.");
		return false;
	}

	_buffer = (char*) calloc(_size, sizeof(char));
	return nullptr != _buffer;
}

char MemoryStreamer::read()
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

int MemoryStreamer::read(
	char* const buffer,
	const int offset,
	const int count)
{
	if (nullptr == _buffer)
	{
		return -1;
	}

	if (offset < 0 || offset >= _size)
	{
		return -1;
	}

	if (count <= 0)
	{
		return -1;
	}

	// read!

	return -1;
}

bool MemoryStreamer::write(const char value)
{
	return false;
}

bool MemoryStreamer::write(char* const buffer, const int offset, const int count)
{
	return false;
}

int MemoryStreamer::seek(const int offset, const int origin)
{
	return -1;
}