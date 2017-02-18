#include "File.h"

#include <Log.h>
#include <Converter.h>

#define FILE_VERSION 1

File::File()
{
	_logger = Log::logger("File");
}

File::~File()
{
	//
}

bool File::init(Streamer* stream, const int offset, const short size)
{
	if (nullptr == stream)
	{
		return false;
	}

	if (offset < 0 || size <= 0)
	{
		return false;
	}

	_stream = stream;
	_offset = offset;

	header.version = FILE_VERSION;
	header.size = size;
	header.numRecords = 0;
	if (header.write(_stream, _offset))
	{
		return true;
	}

	_logger->error("Could not write File header.");
	return false;
}

bool File::load(Streamer* stream, const int offset)
{
	if (nullptr == stream)
	{
		return false;
	}

	if (offset < 0)
	{
		return false;
	}

	_stream = stream;
	_offset = offset;
	
	if (header.read(stream, _offset))
	{
		return true;
	}

	_logger->error("Could not read File header.");
	return false;
}

int File::size()
{
	return header.size;
}

bool File::flush()
{
	// for now, we are always writing to EEPROM
	// TODO: Buffering adds, then writing many at once.

	return true;
}

bool File::add(float value)
{
	// determine if we have the space
	int numBytes = 2 + header.numRecords * 4;
	if (header.size - numBytes < 4)
	{
		return false;
	}

	// write new value to end of the buffer
	IntUnion converter;
	converter.floatValue = value;
	_stream->write(converter.charValue, _offset + numBytes, 4);

	// update numRecords at beginning
	header.numRecords += 1;
	converter.intValue = header.numRecords;
	_stream->write(converter.charValue, _offset, 4);

	return false;
}