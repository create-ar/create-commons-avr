#include "Messaging.h"
#include "Message.h"
#include "crc.h"

// Milliseconds a request can be out before it expires.
const int MESSAGING_TIMEOUT_MILLIS = 3 * 1000;

// size of the packet header, in bytes
const int MESSAGE_HEADER_SIZE = 10;

// identifier used in packet header
const int MESSAGE_IDENTIFIER_LEN = 4;
const unsigned char MESSAGE_IDENTIFIER[MESSAGE_IDENTIFIER_LEN] = { 'O', 'F', 'P', 'H' };

// used in rand()
static unsigned long int next = 1;

// Standard rand() implementation
int rand(void)  /* RAND_MAX assumed to be 32767. */
{
	next = next * 1103515245 + 12345;
	return (unsigned)(next / 65536) % 32768;
}

// Requires session to read and write.
Messaging::Messaging(
	Session* session,
	MessageFactory* factory)
	:
	_reader(),
	_writer(MESSAGING_MAX_PACKET_SIZE)
{
	_session = session;
	_factory = factory;
	_index = 0;
}

// sets a handler for a specific packet type
void Messaging::handle(
	uint16_t packetType,
	void(*handler)(Message*))
{
	Messaging_HandlerRecord *record = new Messaging_HandlerRecord();
	record->packetType = packetType;
	record->handler = handler;
	
	_handlers->add(record);
}

// removes a handler for a specific packet type
void Messaging::unhandle(uint16_t packetType)
{
	LinkedListIterator<Messaging_HandlerRecord>* it = _handlers->it();
	while (it->moveNext())
	{
		Messaging_HandlerRecord* record = it->current();
		if (record->packetType == packetType)
		{
			_handlers->remove(record);

			delete record;

			break;
		}
	}

	delete it;
}

// sends a message
const void Messaging::send(Message* message)
{
	// id does not need to be a good random number
	uint16_t id = rand() % 32767;

	// header
	_writer.writeBytes(MESSAGE_IDENTIFIER, 4);
	_writer.writeShort(message->getPacketType());
	_writer.writeShort(id);

	// payload length placeholder
	int index = _writer.index;
	_writer.writeShort(0);

	// write payload
	int payloadStart = _writer.index;
	message->writePayload(&_writer);

	// go back and write real payload length
	int lastIndex = _writer.index;
	int payloadLen = lastIndex - payloadStart;
	_writer.index = index;
	_writer.writeShort(lastIndex - index);
	_writer.index = lastIndex;

	// crc
	int len;
	unsigned char* writeBuffer = _writer.getBuffer(&len);
	_writer.writeShort(crc16(
		writeBuffer,
		payloadStart,
		payloadLen));

	// write to session
	_session->write(
		writeBuffer,
		_writer.index);
}

// sends a message that expects a response
const void sendRequest(Message*, void(*handler)(Message*))
{

}

// called to read from stream
void Messaging::update()
{
	if (!_session->available())
	{
		return;
	}

	char byte = _session->read();
	if (-1 == byte)
	{
		return;
	}

	_buffer[_index++] = byte;

	if (_index < MESSAGE_HEADER_SIZE)
	{
		return;
	}

	if (!tryReadMessage())
	{
		// could not read a message
	}
}

// attempts to read a message from the buffer
bool Messaging::tryReadMessage()
{
	_reader.setBuffer(_buffer, MESSAGING_MAX_PACKET_SIZE, 0);

	// check identifier
	for (int i = 0; i < MESSAGE_IDENTIFIER_LEN; i++)
	{
		if (MESSAGE_IDENTIFIER[i] != _reader.readByte())
		{
			// junk data, reset buffer
			_index = 0;
			return false;
		}
	}

	uint16_t messageId = _reader.readShort();
	uint16_t packetType = _reader.readShort();

	// get payload length + check buffer size
	uint16_t payloadLen = _reader.readShort();
	int remainingBytes = _index - _reader.getIndex();
	if (remainingBytes < 0 || (static_cast<uint16_t>(remainingBytes) < payloadLen))
	{
		return false;
	}

	// read crc
	int payloadStart = _reader.getIndex();
	_reader.setIndex(payloadStart + payloadLen);
	uint16_t crc = _reader.readShort();
	_reader.setIndex(payloadStart);

	// calculate crc
	uint16_t crcCalc = crc16(
		_buffer,
		_reader.getIndex(),
		payloadLen);

	// data corruption!
	if (crc != crcCalc)
	{
		// TODO: copy remaining to beginning of buffer
		return false;
	}

	// deserialize
	Message* message = _factory->message(packetType);
	message->readPayload(&_reader);

	// handle message
	handleMessage(message, messageId);

	// cleanup message after handlers do something with it
	delete message;

	return true;
}

// called to pass a message to all potential handlers
void Messaging::handleMessage(Message* message, uint16_t messageId)
{
	// requests first
	Messaging_RequestRecord* record = requestRecord(messageId);
	if (nullptr != record)
	{
		record->handler(message);

		_requests->remove(record);

		delete record;
	}

	// handlers
	uint16_t packetType = message->getPacketType();
	LinkedListIterator<Messaging_HandlerRecord>* it = _handlers->it();
	while (it->moveNext())
	{
		Messaging_HandlerRecord* record = it->current();
		if (record->packetType == packetType)
		{
			record->handler(message);

			delete record;

			// start from beginning again
			it->reset();
		}
	}

	delete it;
}

// retrieves a request record by message id
Messaging_RequestRecord* Messaging::requestRecord(uint16_t messageId)
{
	LinkedListIterator<Messaging_RequestRecord>* it = _requests->it();
	while (it->moveNext())
	{
		Messaging_RequestRecord* record = it->current();
		if (record->messageId == messageId)
		{
			delete it;

			return record;
		}
	}

	delete it;

	return nullptr;
}