#include "StreamWriter.h"

#include <Converter.h>

StreamWriter::StreamWriter(int maxLen)
{
	_bufferLen = maxLen;
	_buffer = new unsigned char[_bufferLen];

	index = 0;
}

StreamWriter::~StreamWriter()
{
	delete _buffer;
}

unsigned char* StreamWriter::getBuffer(int* len)
{
	*len = _bufferLen;

	return _buffer;
}

const void StreamWriter::writeShort(const short value)
{
	ShortUnion converter = ShortUnion();
	converter.shortValue = value;

	_buffer[index++] = converter.charValue[0];
	_buffer[index++] = converter.charValue[1];
}

const void StreamWriter::writeInt(const int value)
{
	IntUnion converter = IntUnion();
	converter.intValue = value;

	_buffer[index++] = converter.charValue[0];
	_buffer[index++] = converter.charValue[1];
	_buffer[index++] = converter.charValue[2];
	_buffer[index++] = converter.charValue[3];
}

const void StreamWriter::writeByte(const unsigned char value)
{
	_buffer[index++] = value;
}

const void StreamWriter::writeBytes(const unsigned char* bytes, const short len)
{
	writeShort(len);

	for (int i = 0; i < len; i++)
	{
		_buffer[index++] = bytes[i];
	}
}

const void StreamWriter::writeIntAsByte(const int value)
{
	_buffer[index++] = value + '0';
}

const void StreamWriter::writeBool(const bool value)
{
	_buffer[index++] = value ? 1 : 0;
}