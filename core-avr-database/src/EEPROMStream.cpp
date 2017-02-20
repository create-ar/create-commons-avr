#include "EEPROMStream.h"

EEPROMStream::EEPROMStream()
{
	_dataFlash = Dataflash();
}

bool EEPROMStream::init(PinConfiguration pins)
{
	return false;
}

char EEPROMStream::read()
{
	return 0;
}

int EEPROMStream::read(char* const buffer, const int offset, const int count)
{
	return 0;
}

bool EEPROMStream::write(const char value)
{
	return false;
}

int EEPROMStream::write(char* const buffer, const int offset, const int count)
{
	return -1;
}

int EEPROMStream::seek(const int offset, const int origin)
{
	return 0;
}