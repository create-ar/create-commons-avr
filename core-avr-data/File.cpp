#include "File.h"

File::File(EEPROMStream* stream, const int offset, const int size)
{
	//
}

int File::size()
{
	return 0;
}

bool flush()
{
	return false;
}

bool refresh()
{
	return false;
}

bool add(const char* buffer, const int offset, const int size)
{
	return false;
}

bool update(
	const char* buffer,
	const int sourceOffset,
	const int sourceSize,
	const int targetOffset)
{
	return false;
}