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

int32_t EEPROMStream::get_index()
{
	return 0;
}

char EEPROMStream::read()
{
	return -1;
}

int32_t EEPROMStream::read(unsigned char* const buffer, const int32_t offset, const int32_t count)
{
	return -1;
}

bool EEPROMStream::write(const unsigned char value)
{
	return false;
}

int32_t EEPROMStream::write(unsigned char* const buffer, const int32_t offset, const int32_t count)
{
	return -1;
}

int32_t EEPROMStream::set(const unsigned char value, const int32_t offset, const int32_t count)
{
	return -1;
}

int32_t EEPROMStream::seek(const int32_t offset, const int32_t origin)
{
	return -1;
}