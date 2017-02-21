#include "EEPROMStream.h"

EEPROMStream::EEPROMStream()
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

int read(char* const buffer, const int offset, const int count)
{
	return -1;
}

bool write(const char value)
{
	return false;
}

int write(char* const buffer, const int offset, const int count)
{
	return -1;
}

int set(const char value, const int offset, const int count)
{
	return -1;
}

int seek(const int offset, const int origin)
{
	return -1;
}