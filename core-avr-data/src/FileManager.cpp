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
	if (_header.read(_stream))
	{
		if (_header.totalBytes == config.totalBytes)
		{
			return true;
		}

		return false;
	}

	return false;
}

bool FileManager::init(FileManagerConfig config)
{
	_header.version = FILEMANAGER_VERSION;
	_header.numFiles = 0;
	_header.usedBytes = 0;
	_header.totalBytes = config.totalBytes;

	if (_header.write(_stream))
	{
		return true;
	}

	_logger->error("Could not write new header.");
	return false;
}

File* FileManager::create(const char* uri, const int size)
{
	int totalSize = size + FILE_HEADER_SIZE;

	// first, check if we have the room left
	if (_header.totalBytes - _header.usedBytes < totalSize)
	{
		_logger->error("Not enough storage to create file.");
		return nullptr;
	}

	// set that memory to 0
	int absoluteOffset = FILEMANAGER_HEADER_SIZE + _header.usedBytes;
	_stream->set('\0', absoluteOffset, size);

	// create a file
	File* file = new File();
	if (!file->init(_stream, absoluteOffset, size))
	{
		delete file;
		return nullptr;
	}

	return file;
}

File* FileManager::get(const char* uri)
{
	if (0 == _header.numFiles)
	{
		return nullptr;
	}

	int offset = FILE_HEADER_SIZE;
	FileHeader fileHeader;

	// read in header
	while (offset < _header.usedBytes)
	{
		if (fileHeader.read(_stream, offset))
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