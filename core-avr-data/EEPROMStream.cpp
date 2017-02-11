#include "EEPROMStream.h"

char EEPROMStream::read()
{
	return 0;
}

int EEPROMStream::read(char* buffer, const int offset, const int count)
{
	return 0;
}

bool EEPROMStream::write(const char value)
{
	return false;
}

bool EEPROMStream::write(const char* buffer, const int offset, const int count)
{
	return false;
}

int EEPROMStream::seek(const int offset, const int origin)
{
	return 0;
}