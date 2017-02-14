// 
// 
// 

#include "Message.h"

// constructor
Message::Message(short packetType)
{
	_packetType = packetType;
}

// destructor
Message::~Message()
{

}

// retrieves the packet type
short Message::getPacketType()
{
	return _packetType;
}