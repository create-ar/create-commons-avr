#include "DatabaseManager.h"

#include <stdlib.h>
#include <Log.h>

#define DATABASEMANAGER_VERSION 1

static char VALID_IDENTIFIER[IDENTIFIER_LENGTH] = {'O', 'F', 'F', 'H'};

DatabaseManager::DatabaseManager(AvrStream* stream)
{
	_stream = stream;
	_logger = Log::logger("DatabaseManager");
}

DatabaseManager::~DatabaseManager()
{
	
}

bool DatabaseManager::load(DatabaseManagerConfig config)
{
	if (_stream->read((char *) &_header, 0, DATABASEMANAGER_HEADER_SIZE))
	{
		if (0 != strncmp(_header.identifier, VALID_IDENTIFIER, IDENTIFIER_LENGTH))
		{
			return false;
		}

		if (_header.totalBytes != config.totalBytes)
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

	memcpy(_header.identifier, VALID_IDENTIFIER, IDENTIFIER_LENGTH);
	_header.version = DATABASEMANAGER_VERSION;
	_header.numDatabases = 0;
	_header.usedBytes = 0;
	_header.totalBytes = config.totalBytes;

	if (_stream->write((char*) &_header, 0, DATABASEMANAGER_HEADER_SIZE))
	{
		return true;
	}

	return false;
}

Database* DatabaseManager::create(const char* uri, const int size)
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
	if (_header.totalBytes - _header.usedBytes < totalSize)
	{
		return nullptr;
	}

	// set that memory to 0
	int absoluteOffset = DATABASEMANAGER_HEADER_SIZE + _header.usedBytes;
	_stream->set('\0', absoluteOffset, size);

	// create a file
	Database* file = new Database();
	if (!file->init(_stream, absoluteOffset, size, uri))
	{
		delete file;
		return nullptr;
	}

	_header.numDatabases += 1;
	_header.usedBytes += totalSize;

	return file;
}

Database* DatabaseManager::get(const char* uri)
{
	if (nullptr == uri)
	{
		return nullptr;
	}

	if (0 == _header.numDatabases)
	{
		throw "No files!";
		return nullptr;
	}

	// start looking through files right after the header
	unsigned int offset = DATABASEMANAGER_HEADER_SIZE;
	DatabaseHeader fileHeader;

	while (offset < DATABASEMANAGER_HEADER_SIZE + _header.usedBytes)
	{
		if (DATABASE_HEADER_SIZE == _stream->read(
			(char*) &fileHeader,
			offset,
			DATABASE_HEADER_SIZE))
		{
			if (0 == strncmp(
				(const char*) fileHeader.uri,
				uri,
				strlen(uri)))
			{
				Database* file = new Database();
				if (!file->load(_stream, offset))
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