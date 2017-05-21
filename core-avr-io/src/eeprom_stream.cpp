#include "eeprom_stream.h"

EEPROMStream::EEPROMStream(uint32_t pageSize, uint32_t numPages) :
	_pageSize(pageSize),
	_numPages(numPages)
{
	
}

EEPROMStream::~EEPROMStream()
{
	
}

bool EEPROMStream::init(PinConfiguration pins)
{
	return false;
}

char read()
{
	return -1;
}

int32_t read(char* const buffer, const int32_t offset, const int32_t count)
{
	return -1;
}

bool write(const char value)
{
	return false;
}

int32_t write(char* const buffer, const int32_t offset, const int32_t count)
{
	return -1;
}

int32_t set(const char value, const int32_t offset, const int32_t count)
{
	return -1;
}

int32_t seek(const int32_t offset, const int32_t origin)
{
	return -1;
}