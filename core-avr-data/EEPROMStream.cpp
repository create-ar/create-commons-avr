#include "EEPROMStream.h"

EEPROMStream::EEPROMStream()
{
	_dataFlash = Dataflash();
}

bool EEPROMStream::init(int dataout, int datain, int spiclock, int slaveselect)
{
	_dataFlash.init(dataout, datain, spiclock, slaveselect);

	return false;
}

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