// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#include "StreamReader.h"
#include "StreamWriter.h"

class Message
{
private:
	// specific to type of packet
	short _packetType;

public:
	// constructor
	Message(short packetType);

	// destructor!
	virtual ~Message();

	// return packet type
	short getPacketType();

	// reads the message from a stream
	virtual void readPayload(StreamReader* reader) = 0;

	// writes the message to a stream
	virtual void writePayload(StreamWriter* writer) = 0;
};

#endif

