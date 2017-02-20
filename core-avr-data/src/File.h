#ifndef FILE_H
#define FILE_H

#include "Streamer.h"

#include <string.h>
#include <Converter.h>
#include <Logger.h>

#define FILE_URI_SIZE 16

/**
 * @brief      Description of file, stored at the start of the file buffer.
 */
struct FileHeader
{
	/**
	 * Version of the file.
	 */
	int version;

	/**
	 * Number of bytes, excluding the header.
	 */
	short contentSize;

	/**
	 * Number of records total.
	 */
	short numRecords;

	/**
	 * Uri.
	 */
	char uri[FILE_URI_SIZE];
};

#define FILE_HEADER_SIZE sizeof(FileHeader)

/**
 * @brief      Entry point for adding data to + updating fixed size files.
 */
class File
{
private:

	/**
	 * Logger.
	 */
	Logger* _logger;

	/**
	 * Stream to read/write with.
	 */
	Streamer* _stream;

	/**
	 * Byte offset into stream.
	 */
	int _offset;

	/**
	 * Buffer used internally to move floats around.
	 */
	char _scratchBuffer[4];

public:

	/**
	 * Header information.
	 */
	FileHeader header;

	/**
	 * @brief      Constructor.
	 */
	File();

	/**
	 * @brief      Destructor.
	 */
	~File();

	/**
	 * @brief      Loads header into memory. This is for Files that already
	 * exist.
	 *
	 * @param      stream  The stream to read/write from.
	 * @param[in]  offset  The byte offset this file starts at.
	 * 
	 * @return     True if the file was successfully loaded.
	 */
	bool load(Streamer* stream, const int offset);

	/**
	 * @brief      Writes header to disk. This is for new Files.
	 *
	 * @param      stream  The stream to write to.
	 * @param[in]  offset  The byte offset this file starts at.
	 * @param[in]  contentSize    The size, in bytes, of the file.
	 * @param[in]  uri    The uri of the resource.
	 *
	 * @return     True if the file was successfully written.
	 */
	bool init(Streamer* stream, const int offset, const short contentSize, const char* uri);

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

	/**
	 * @brief      Total number of stored values.
	 *
	 * @return     Total number of float values stored.
	 */
	float numValues();

	/**
	 * @brief      Retrieves values.
	 *
	 * @param[in]  buffer   Buffer to copy values into.
	 * @param[in]  recordOffset  The starting index of values.
	 * @param[in]  recordCount   The number of values to copy into the buffer.
	 *
	 * @return     Returns the number of values copied.
	 */
	int values(float* buffer, const int recordDffset, const int recordCount);
};

#endif