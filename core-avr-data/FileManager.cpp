#include "FileManager.h"

FileManager::FileManager()
{
	_stream = EEPROMStream();
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

	// read header

	return false;
}

File* FileManager::create(const char* uri, const int size)
{
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