#include "EEPROMStream.h"

/**
 * @brief      Entry point for adding data to + updating fixed size files.
 */
class File
{
private:
	EEPROMStream* _stream;

public:
	/**
	 * @brief      Creates a fixed size file.
	 *
	 * @param      stream  The stream to read/write from.
	 * @param[in]  offset  The byte offset this file starts at.
	 * @param[in]  size    The size of the file, in bytes.
	 */
	File(EEPROMStream* stream, const int offset, const int size);

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
	 * @brief      Essentially a revert, refreshes the file from data.
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool refresh();

	/**
	 * @brief      Adds a block of bytes to somewhere in the file.
	 *
	 * @param[in]  buffer  The buffer to copy from.
	 * @param[in]  offset  The byte offset, relative to the file, to start at.
	 * @param[in]  size    The size of the buffer, in bytes.
	 *
	 * @return     Returns true iff the add was successful.
	 */
	bool add(const char* buffer, const int offset, const int size);
	
	/**
	 * @brief      Updates a block of memory.
	 *
	 * @param[in]  buffer        The buffer to copy data from.
	 * @param[in]  sourceOffset  The byte offset of the source buffer.
	 * @param[in]  sourceSize    The size of the memory block to copy, in bytes. 
	 * @param[in]  targetOffset  The target byte offset, relative to the file, to start at.
	 *
	 * @return     Returns true iff the add was successful.
	 */
	bool update(
		const char* buffer,
		const int sourceOffset,
		const int sourceSize,
		const int targetOffset);
};