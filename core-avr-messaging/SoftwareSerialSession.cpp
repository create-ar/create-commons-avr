#include "SoftwareSerialSession.h"

// constructor.
SoftwareSerialSession::SoftwareSerialSession(
	int rx,
	int tx,
	int baud)
	:_serial(rx, tx)
{
	_serial.begin(baud);
}

// returns true if bytes are available
bool SoftwareSerialSession::available()
{
	return _serial.available();
}

// writes a buffer
void SoftwareSerialSession::write(const unsigned char* buffer, const int size)
{
	_serial.write((char *) buffer, size);
}

// reads a single char
char SoftwareSerialSession::read()
{
	return _serial.read();
}