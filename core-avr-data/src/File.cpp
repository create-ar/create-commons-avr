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

bool File::init(Streamer* stream, const int offset, const short contentSize)
{
	if (nullptr == stream)
	{
		return false;
	}

	if (offset < 0 || contentSize <= 0)
	{
		return false;
	}

	header.version = FILE_VERSION;
	header.contentSize = contentSize;
	header.numRecords = 0;

	if (header.write(stream, offset))
	{
		_stream = stream;
		_offset = offset;

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
	
	if (header.read(stream, offset))
	{
		_stream = stream;
		_offset = offset;

		return true;
	}

	_logger->error("Could not read File header.");
	return false;
}

bool File::flush()
{
	header.write(_stream, _offset);

	return true;
}

bool File::add(float value)
{
	if (nullptr == _stream)
	{
		return false;
	}

	// determine if we have the space
	int numRecordBytes = header.numRecords * 4;
	if (header.contentSize - numRecordBytes < 4)
	{
		return false;
	}

	// write new value to end of the buffer
	int absByteIndex = _offset + FILE_HEADER_SIZE + 4 * header.numRecords;
	int numBytesWritten = _stream->write((char*) &value, absByteIndex, 4);

	if (4 != numBytesWritten)
	{
		return false;
	}

	// update numRecords-- not written till flush()
	header.numRecords += 1;

	return true;
}

float File::numValues()
{
	return header.numRecords;
}

int File::values(float* buffer, const int recordOffset, const int recordCount)
{
	if (nullptr == _stream)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (recordOffset < 0 || recordOffset > header.numRecords || recordCount < 0)
	{
		return -1;
	}

	// just print everything
	int startAbsByteIndex = _offset + FILE_HEADER_SIZE + 4 * recordOffset;
	int endAbsByteIndex = startAbsByteIndex + 4 * recordCount;
	int byteLen = endAbsByteIndex - startAbsByteIndex;

	int readLen = _stream->read((char*) buffer, startAbsByteIndex, byteLen);
	if (readLen != byteLen)
	{
		throw "Error";
	}

	return readLen / 4;
}