#include "File.h"
#include "..\common\Converter.h"

File::File(EEPROMStream* stream, const int offset, const short size)
{
	_stream = stream;
	_offset = offset;
	_size = size;
}

int File::size()
{
	return _size;
}

bool File::flush()
{
	// for now, we are always writing to EEPROM
	// TODO: Buffering adds, then writing many at once.

	return true;
}

bool File::add(float value)
{
	readHeaderInfo();

	// determine if we have the space
	int numBytes = 2 + _numRecords * 4;
	if (_size - numBytes < 4)
	{
		return false;
	}

	// write new value to end of the buffer
	IntUnion converter;
	converter.floatValue = value;
	_stream->write(converter.charValue, _offset + numBytes, 4);

	// update numRecords at beginning
	_numRecords += 1;
	converter.intValue = _numRecords;
	_stream->write(converter.charValue, _offset, 4);

	return false;
}

/**
 * @brief      Reads header information from the buffer.
 */
void File::readHeaderInfo()
{
	if (-1 == _numRecords)
	{
		ShortUnion converter;
		_stream->read(converter.charValue, _offset, 2);

		_numRecords = converter.shortValue;
	}
}