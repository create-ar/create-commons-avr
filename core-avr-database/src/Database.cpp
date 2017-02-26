#include "Database.h"

#include <Log.h>

#define DATABASE_VERSION 1

Database::Database(AvrClock* clock)
{
	_logger = Log::logger("Database");
	_clock = clock;
}

Database::~Database()
{
	//
}

bool Database::init(
	AvrStream* stream,
	const int offset,
	const short contentSize,
	const char valuesPerRecord,
	const char* uri)
{
	if (nullptr == stream)
	{
		return false;
	}

	if (offset < 0 || contentSize <= 0)
	{
		return false;
	}

	if (valuesPerRecord <= 0)
	{
		return false;
	}

	if (nullptr == uri)
	{
		return false;
	}

	header.version = DATABASE_VERSION;
	header.contentSize = contentSize;
	header.valuesPerRecord = valuesPerRecord;
	header.numRecords = 0;

	memset((char*) header.uri, '\0', DATABASE_URI_SIZE);
	memcpy(&header.uri, uri, DATABASE_URI_SIZE);

	if (DATABASE_HEADER_SIZE == stream->write(
		(char*) &header,
		offset,
		DATABASE_HEADER_SIZE))
	{
		_stream = stream;
		_offset = offset;
		_bytesPerRecord = (1 /* timestamp */ + header.valuesPerRecord) * 4 /* bytes per float */;

		return true;
	}

	return false;
}

bool Database::load(AvrStream* stream, const int offset)
{
	if (nullptr == stream)
	{
		return false;
	}

	if (offset < 0)
	{
		return false;
	}
	
	if (DATABASE_HEADER_SIZE == stream->read(
		(char*) &header,
		offset,
		DATABASE_HEADER_SIZE))
	{
		_stream = stream;
		_offset = offset;
		_bytesPerRecord = (1 + header.valuesPerRecord) * 4;

		return true;
	}

	return false;
}

bool Database::flush()
{
	if (nullptr == _stream)
	{
		return false;
	}

	return DATABASE_HEADER_SIZE == _stream->write(
		(char*) &header,
		_offset,
		DATABASE_HEADER_SIZE);
}

bool Database::add(const float* value)
{
	if (nullptr == _stream)
	{
		return false;
	}

	// determine if we have the space
	int numRecordBytes = header.numRecords * _bytesPerRecord;
	if (header.contentSize - numRecordBytes < _bytesPerRecord)
	{
		return false;
	}

	// write a new set of values to the stream
	// [		   RECORD		  ]
	// [TIMESTAMP][VALUE]...[VALUE]
	{
		// locate index into stream
		int absByteIndex = _offset
			+ DATABASE_HEADER_SIZE
			+ _bytesPerRecord * header.numRecords;

		// write timestamp
		unsigned long timestamp = _clock->now();
		int numBytesWritten = _stream->write(
			(char*) &timestamp,
			absByteIndex,
			4);

		// write values
		numBytesWritten += _stream->write(
			(char*) value,
			absByteIndex + 4,
			header.valuesPerRecord * 4);

		if (_bytesPerRecord != numBytesWritten)
		{
			return false;
		}

		// update numRecords-- not written till flush()
		header.numRecords += 1;
	}

	return true;
}

float Database::numRecords()
{
	return header.numRecords;
}

int Database::dump(
	char* buffer,
	const int recordOffset,
	const int recordCount)
{
	if (nullptr == _stream)
	{
		return -1;
	}

	if (nullptr == buffer)
	{
		return -1;
	}

	if (recordOffset < 0
		|| recordOffset >= header.numRecords
		|| recordCount < 0)
	{
		return -1;
	}

	int startAbsByteIndex = _offset
		+ DATABASE_HEADER_SIZE
		+ _bytesPerRecord * recordOffset;
	int endAbsByteIndex = startAbsByteIndex + _bytesPerRecord * recordCount;
	int byteLen = endAbsByteIndex - startAbsByteIndex;

	int readLen = _stream->read(buffer, startAbsByteIndex, byteLen);
	if (readLen != byteLen)
	{
		return -1;
	}

	return readLen / _bytesPerRecord;
}