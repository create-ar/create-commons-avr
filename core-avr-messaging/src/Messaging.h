// Messaging.h

#ifndef _MESSAGING_h
#define _MESSAGING_h

#include <inttypes.h>

#include "../core-avr-ds/LinkedList.h"

#include "StreamReader.h"
#include "StreamWriter.h"
#include "Session.h"
#include "Message.h"
#include "MessageFactory.h"

// maximum packet size
#define MESSAGING_MAX_PACKET_SIZE 512

// keeps track of handling information for different packet types
struct Messaging_HandlerRecord
{
	uint16_t packetType;
	void(*handler)(Message*);
};

// keeps track of request/response pairs
struct Messaging_RequestRecord
{
	uint16_t messageId;
	void(*handler)(Message*);
};

// sends and receives messages over a serial interface
class Messaging
{
private:
	// input/output
	Session* _session;

	// creates Messages
	MessageFactory* _factory;

	// for using a stream
	StreamReader _reader;
	StreamWriter _writer;

	// tracks handling information for different packet types
	LinkedList<Messaging_HandlerRecord>* _handlers;

	// tracks handling information for requests/responses
	LinkedList<Messaging_RequestRecord>* _requests;

	// holds incoming queue
	int _index;
	unsigned char _buffer[MESSAGING_MAX_PACKET_SIZE];

	// tries to read a message
	bool tryReadMessage();

	// handles a message
	void handleMessage(Message* message, uint16_t messageId);

	// retrieves a request record by message id
	Messaging_RequestRecord* requestRecord(uint16_t messageId);

public:
	// requires a session and a way to create messages
	Messaging(Session*, MessageFactory*);

	// sets a handler for a specific packet type
	void handle(
		uint16_t packetType,
		void(*handler)(Message*));

	// removes a handler for a specific packet type
	void unhandle(uint16_t packetType);

	// sends a message
	const void send(Message*);

	// sends a message that expects a response
	const void sendRequest(Message*, void(*handler)(Message*));

	// call to read from stream
	void update();
};

#endif

