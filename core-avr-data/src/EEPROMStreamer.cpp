#include "EEPROMStreamer.h"

EEPROMStreamer::EEPROMStreamer()
{
	_dataFlash = Dataflash();
}

bool EEPROMStreamer::init(PinConfiguration pins)
{
	//_dataFlash.init(dataout, datain, spiclock, slaveselect);

	return false;
}

char EEPROMStreamer::read()
{
	return 0;
}

int EEPROMStreamer::read(char* const buffer, const int offset, const int count)
{
	return 0;
}

bool EEPROMStreamer::write(const char value)
{
	return false;
}

bool EEPROMStreamer::write(char* const buffer, const int offset, const int count)
{
	return false;
}

int EEPROMStreamer::seek(const int offset, const int origin)
{
	return 0;
}