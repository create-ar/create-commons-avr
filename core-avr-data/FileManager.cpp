#include "FileManager.h"

FileManager::FileManager()
{
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
	_header.version = 1;
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
	// first, check if we have the room left 
	if (_totalSize - _header.totalBytes < size)
	{
		_logger->error("Not enough storage to create file.");
		return nullptr;
	}



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