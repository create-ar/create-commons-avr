#ifndef MESSAGEFACTORY_h
#define MESSAGEFACTORY_h

#include <inttypes.h>

#include "Message.h"

// class that creates new messages
class MessageFactory
{
public:

	// creates a message for a specific type of packet
	virtual Message* message(uint16_t packetType) = 0;
};
#endif