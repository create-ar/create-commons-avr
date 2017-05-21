#include "DatabaseManager.h"

#include <stdlib.h>
#include <Log.h>

#define DATABASEMANAGER_VERSION 1

static char VALID_IDENTIFIER[IDENTIFIER_LENGTH] = {'O', 'F', 'F', 'H'};

DatabaseManager::DatabaseManager(AvrClock* clock, AvrStream* stream)
{
	clock_ = clock;
	stream_ = stream;
	logger_ = Log::logger("DatabaseManager");
}

DatabaseManager::~DatabaseManager()
{
	
}

bool DatabaseManager::load(DatabaseManagerConfig config)
{
	if (stream_->read((char *) &header_, 0, DATABASEMANAGER_HEADER_SIZE))
	{
		if (0 != strncmp(header_.identifier, VALID_IDENTIFIER, IDENTIFIER_LENGTH))
		{
			return false;
		}

		if (header_.totalBytes != config.totalBytes)
		{
			return false;
		}

		return true;
	}

	return false;
}

bool DatabaseManager::init(DatabaseManagerConfig config)
{
	if (0 == config.totalBytes)
	{
		return false;
	}

	memcpy(header_.identifier, VALID_IDENTIFIER, IDENTIFIER_LENGTH);
	header_.version = DATABASEMANAGER_VERSION;
	header_.numDatabases = 0;
	header_.usedBytes = 0;
	header_.totalBytes = config.totalBytes;

	if (stream_->write((char*) &header_, 0, DATABASEMANAGER_HEADER_SIZE))
	{
		return true;
	}

	return false;
}

Database* DatabaseManager::create(
	const char* uri,
	const int size,
	const char valuesPerRecord)
{
	if (nullptr == uri)
	{
		return nullptr;
	}

	if (size <= 0)
	{
		return nullptr;
	}

	int totalSize = size + DATABASE_HEADER_SIZE;

	// first, check if we have the room left
	if (header_.totalBytes - header_.usedBytes < totalSize)
	{
		return nullptr;
	}

	// set that memory to 0
	int absoluteOffset = DATABASEMANAGER_HEADER_SIZE + header_.usedBytes;
	stream_->set('\0', absoluteOffset, size);

	// create a file
	Database* file = new Database(clock_);
	if (!file->init(stream_, absoluteOffset, size, valuesPerRecord, uri))
	{
		delete file;
		return nullptr;
	}

	header_.numDatabases += 1;
	header_.usedBytes += totalSize;

	return file;
}

Database* DatabaseManager::get(const char* uri)
{
	if (nullptr == uri)
	{
		return nullptr;
	}

	if (0 == header_.numDatabases)
	{
		return nullptr;
	}

	// start looking through files right after the header
	unsigned int offset = DATABASEMANAGER_HEADER_SIZE;
	DatabaseHeader fileHeader;

	while (offset < DATABASEMANAGER_HEADER_SIZE + header_.usedBytes)
	{
		if (DATABASE_HEADER_SIZE == stream_->read(
			(char*) &fileHeader,
			offset,
			DATABASE_HEADER_SIZE))
		{
			if (0 == strncmp(
				(const char*) fileHeader.uri,
				uri,
				strlen(uri)))
			{
				Database* file = new Database(clock_);
				if (!file->load(stream_, offset))
				{
					delete file;
					return nullptr;
				}

				return file;
			}

			// move to next file
			offset += DATABASE_HEADER_SIZE + fileHeader.contentSize;
		}
	}
	
	return nullptr;
}

bool DatabaseManager::set(Database* file)
{
	return file->flush();
}