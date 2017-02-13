#include "FileManager.h"
#include <Converter.h>
#include <Log.h>

#define FILEMANAGER_VERSION 1
#define NEW_FILE_BUFFER 128

FileManager::FileManager()
{
	_logger = Log::logger("FileManager");
	_stream = EEPROMStream();
	_files = LinkedList<Tuple<char*, File>>();
}

FileManager::~FileManager()
{
	delete _logger;
}

bool FileManager::init(FileManagerConfig config)
{
	// calculate total size of EEPROM
	_totalSize = config.numPages * config.bytesPerPage;

	bool success = _stream.init(
		config.pinDataOut,
		config.pinDataIn,
		config.pinSpiClock,
		config.pinSlaveSelect);
	if (!success)
	{
		_logger->error("Could not initialize FileManager, stream could not be read from.");
		return false;
	}

	if (_header.read(&_stream))
	{
		return true;
	}

	_logger->info("Could not read header, attempting to format.");

	// header could not be read, so let's create one
	_header.version = FILEMANAGER_VERSION;
	_header.numFiles = 0;
	_header.totalBytes = 0;
	if (_header.write(&_stream))
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
	if (_totalSize - _header.totalBytes < totalSize)
	{
		_logger->error("Not enough storage to create file.");
		return nullptr;
	}

	// find starting absolute offset
	int absoluteOffset = FILEMANAGER_HEADER_SIZE + _header.totalBytes;

	// allocate a small buffer
	const int bufferSize = min(NEW_FILE_BUFFER, size);
	char* memory = (char*) calloc(bufferSize, sizeof(char));
	if (nullptr == memory)
	{
		_logger->error("Could not allocate space: malloc failed.");
		return nullptr;
	}

	// TODO: write header to the stream

	// write to stream until we hit size
	absoluteOffset += FILE_HEADER_SIZE;
	int bytesWritten = 0;
	while (bytesWritten < size)
	{
		int bytesToWrite = min(bufferSize, size - bytesWritten);
		if (!_stream.write(
			memory,
			absoluteOffset,
			bytesToWrite))
		{
			_logger->error("Could not write file.");
			return nullptr;
		}
	}

	// free memory
	free(memory);

	return nullptr;
}

File* FileManager::get(const char* uri)
{
	return nullptr;
}

bool FileManager::set(const File* file)
{
	return false;
}