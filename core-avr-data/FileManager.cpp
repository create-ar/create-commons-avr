#include "FileManager.h"

FileManager::FileManager()
{
	_stream = EEPROMStream();
	_files = LinkedList<Tuple<char*, File>>();
}

FileManager::~FileManager()
{
	//
}

bool FileManager::init(FileManagerConfig config)
{
	bool success = _stream.init(
		config.pinDataOut,
		config.pinDataIn,
		config.pinSpiClock,
		config.pinSlaveSelect);

	return success && _header.read(&_stream);
}

File* FileManager::create(const char* uri, const int size)
{
	// first, check if we have the room left
	

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