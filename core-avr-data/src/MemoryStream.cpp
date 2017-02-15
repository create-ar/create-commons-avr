#include "MemoryStream.h"

#include <stdlib.h>

/**
 * @brief      Stream implementation completely in memory.
 */
class MemoryStream : public Stream
{
public:
	MemoryStream::MemoryStream(const int size)
	{
		_logger = Log::logger("MemoryStream");
		_size = size;
		_index = 0;
	}

	MemoryStream::~MemoryStream()
	{
		free _buffer;
	}

	bool MemoryStream::init(PinConfiguration pins) override
	{
		// already initialized
		if (nullptr != _buffer)
		{
			_logger->warn("MemoryStream already initialized.");
			return false;
		}

		_buffer = (char*) calloc(_size, sizeof(char));
		return nullptr != _buffer;
	}
	
	char MemoryStream::read() override
	{

	}

	int MemoryStream::read(char* const buffer, const int offset, const int count) override
	{

	}

	bool MemoryStream::write(const char value) override
	{

	}

	bool MemoryStream::write(char* const buffer, const int offset, const int count) override
	{

	}

	int MemoryStream::seek(const int offset, const int origin) override
	{

	}
};