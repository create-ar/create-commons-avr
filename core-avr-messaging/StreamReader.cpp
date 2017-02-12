// 
// 
// 

#include "StreamReader.h"
#include "..\common\Converter.h"

StreamReader::StreamReader()
{
	_index = 0;
	_bufferLength = 0;
}

unsigned char* StreamReader::getBuffer()
{
	return _buffer;
}

void StreamReader::setBuffer(
	unsigned char* buffer,
	int length,
	int index)
{
	_buffer = buffer;
	_bufferLength = length;
	_index = index;
}

int StreamReader::getIndex()
{
	return _index;
}

void StreamReader::setIndex(int index)
{
	_index = index;
}

short StreamReader::readShort()
{
	ShortUnion converter;
	converter.charValue[0] = _buffer[_index];
	converter.charValue[1] = _buffer[_index + 1];

	_index += 2;

	return converter.shortValue;
}

int StreamReader::readInt()
{
	IntUnion converter;
	converter.charValue[0] = _buffer[_index++];
	converter.charValue[1] = _buffer[_index++];
	converter.charValue[2] = _buffer[_index++];
	converter.charValue[3] = _buffer[_index++];

	return converter.intValue;
}

unsigned char StreamReader::readByte()
{
	return _buffer[_index++];
}

void StreamReader::readBytes(unsigned char* value, short& len)
{
	len = readShort();
	value = new unsigned char[len];

	for (int i = 0; i < len; i++)
	{
		value[i] = _buffer[_index + i];
	}

	_index += len;
}

int StreamReader::readByteAsInt()
{
	return _buffer[_index++] - '0';
}

bool StreamReader::readBool()
{
	return !(_buffer[_index++] & 0);
}