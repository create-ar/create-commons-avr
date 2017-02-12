#ifndef FILE_H
#define FILE_H

#include "EEPROMStream.h"

/**
 * @brief      Entry point for adding data to + updating fixed size files.
 */
class File
{
private:
	/**
	 * Stream to read/write with.
	 */
	EEPROMStream* _stream;

	/**
	 * Byte offset into stream.
	 */
	int _offset;

	/**
	 * Size in bytes.
	 */
	short _size;

	/**
	 * How many records have been written.
	 */
	short _numRecords;

	/**
	 * Buffer used internally to move floats around.
	 */
	char _scratchBuffer[4];

	/**
	 * @brief      Reads header info from buffer.
	 */
	void readHeaderInfo();

public:
	/**
	 * @brief      Creates a fixed size file.
	 *
	 * @param      stream  The stream to read/write from.
	 * @param[in]  offset  The byte offset this file starts at.
	 * @param[in]  size    The size of the file, in bytes.
	 */
	File(EEPROMStream* stream, const int offset, const short size);

	/**
	 * @brief      Retrieves the size of the file.
	 *
	 * @return     Returns the size of the file, in bytes.
	 */
	int size();

	/**
	 * @brief      Flushes any changes to the stream, in case the File decides
	 * to cache.
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool flush();

	/**
	 * @brief      Adds a value to the file.
	 *
	 * @param[in]  value	The float to add to the file.
	 *
	 * @return     Returns true iff the add was successful.
	 */
	bool add(float value);
};

#endif