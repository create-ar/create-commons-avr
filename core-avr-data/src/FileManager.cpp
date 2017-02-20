#include "FileManager.h"

#include <stdlib.h>
#include <Converter.h>
#include <Log.h>

#define FILEMANAGER_VERSION 1
#define NEW_FILE_BUFFER 128

FileManager::FileManager(Streamer* stream)
{
	_stream = stream;
	_logger = Log::logger("FileManager");
}

FileManager::~FileManager()
{
	
}

bool FileManager::load(FileManagerConfig config)
{
	if (_stream->read((char *) &_header, 0, FILEMANAGER_HEADER_SIZE))
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

bool FileManager::init(FileManagerConfig config)
{
	if (0 == config.totalBytes)
	{
		return false;
	}

	memcpy(_header.identifier, VALID_IDENTIFIER, IDENTIFIER_LENGTH);
	_header.version = FILEMANAGER_VERSION;
	_header.numFiles = 0;
	_header.usedBytes = 0;
	_header.totalBytes = config.totalBytes;

	if (_stream->write((char*) &_header, 0, FILEMANAGER_HEADER_SIZE))
	{
		return true;
	}

	return false;
}

File* FileManager::create(const char* uri, const int size)
{
	if (nullptr == uri)
	{
		return nullptr;
	}

	if (size <= 0)
	{
		return nullptr;
	}

	int totalSize = size + FILE_HEADER_SIZE;

	// first, check if we have the room left
	if (_header.totalBytes - _header.usedBytes < totalSize)
	{
		return nullptr;
	}

	// set that memory to 0
	int absoluteOffset = FILEMANAGER_HEADER_SIZE + _header.usedBytes;
	_stream->set('\0', absoluteOffset, size);

	// create a file
	File* file = new File();
	if (!file->init(_stream, absoluteOffset, size, uri))
	{
		delete file;
		return nullptr;
	}

	_header.numFiles += 1;
	_header.usedBytes += totalSize;

	return file;
}

File* FileManager::get(const char* uri)
{
	if (nullptr == uri)
	{
		return nullptr;
	}

	if (0 == _header.numFiles)
	{
		return nullptr;
	}

	int offset = FILE_HEADER_SIZE;
	FileHeader fileHeader;

	// read in header
	while (offset < _header.usedBytes)
	{
		if (FILE_HEADER_SIZE == _stream->read(
			(char*) &fileHeader,
			offset,
			FILE_HEADER_SIZE))
		{
			if (0 == strcmp(
				(const char*) fileHeader.uri,
				uri))
			{
				File* file = new File();
				if (!file->load(_stream, offset))
				{
					delete file;

					_logger->warn("Found file, but could not load it.");

					return nullptr;
				}

				return file;
			}

			// move to next file
			offset += FILE_HEADER_SIZE + fileHeader.contentSize;
		}
	}

	return nullptr;
}

bool FileManager::set(File* file)
{
	return file->flush();
}