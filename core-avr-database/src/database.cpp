#include "database.h"

#include <log.h>

#define DATABASE_VERSION 1

Database::Database(AvrClock* clock)
	:clock_(clock)
{
	logger_ = Log::logger("Database");
}

Database::~Database()
{
	//
}

bool Database::init(
	AvrStream* stream,
	const int32_t offset,
	const int16_t contentSize,
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
		stream_ = stream;
		offset_ = offset;
		bytesPerRecord_ = (1 /* timestamp */ + header.valuesPerRecord) * 4 /* bytes per float */;

		return true;
	}

	return false;
}

bool Database::load(AvrStream* stream, const int32_t offset)
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
		stream_ = stream;
		offset_ = offset;
		bytesPerRecord_ = (1 + header.valuesPerRecord) * 4;

		return true;
	}

	return false;
}

bool Database::flush()
{
	if (nullptr == stream_)
	{
		return false;
	}

	return DATABASE_HEADER_SIZE == stream_->write(
		(char*) &header,
		offset_,
		DATABASE_HEADER_SIZE);
}

bool Database::add(const float* value)
{
	if (nullptr == stream_)
	{
		return false;
	}

	// determine if we have the space
	int numRecordBytes = header.numRecords * bytesPerRecord_;
	if (header.contentSize - numRecordBytes < bytesPerRecord_)
	{
		return false;
	}

	// write a new set of values to the stream
	// [		   RECORD		  ]
	// [TIMESTAMP][VALUE]...[VALUE]
	{
		// locate index into stream
		int32_t absByteIndex = offset_
			+ DATABASE_HEADER_SIZE
			+ bytesPerRecord_ * header.numRecords;

		// write timestamp
		uint32_t timestamp = clock_->now();
		int32_t numBytesWritten = stream_->write(
			(char*) &timestamp,
			absByteIndex,
			4);

		// write values
		numBytesWritten += stream_->write(
			(char*) value,
			absByteIndex + 4,
			header.valuesPerRecord * 4);

		if (bytesPerRecord_ != numBytesWritten)
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

int32_t Database::dump(
	char* buffer,
	const int32_t recordOffset,
	const int32_t recordCount)
{
	if (nullptr == stream_)
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

	int32_t startAbsByteIndex = offset_
		+ DATABASE_HEADER_SIZE
		+ bytesPerRecord_ * recordOffset;
	int32_t endAbsByteIndex = startAbsByteIndex + bytesPerRecord_ * recordCount;
	int32_t byteLen = endAbsByteIndex - startAbsByteIndex;

	int32_t readLen = stream_->read(buffer, startAbsByteIndex, byteLen);
	if (readLen != byteLen)
	{
		return -1;
	}

	return readLen / bytesPerRecord_;
}