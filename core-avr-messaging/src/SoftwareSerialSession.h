#include<SoftwareSerial.h>

#include "Session.h"

#ifndef _SOFTWARESERIALSESSION_h
#define _SOFTWARESERIALSESSION_h

// session implementation on top of SoftwareSerial
class SoftwareSerialSession : public Session
{
private:
	SoftwareSerial _serial;

public:
	// requires receive and send pins
	SoftwareSerialSession(
		int rx,
		int tx,
		int baud);

	// true if bytes are available
	virtual bool available();

	// writes a buffer
	virtual void write(const unsigned char* buffer, const int size);

	// reads a single char
	virtual char read();
};

#endif