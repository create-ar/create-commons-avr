#ifndef DATABASE_H
#define DATABASE_H

#include "AvrStream.h"
#include "AvrClock.h"

#include <string.h>
#include <Logger.h>

#define DATABASE_URI_SIZE 64

/**
 * @brief      Description of file, stored at the start of the file buffer.
 */
struct DatabaseHeader
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
	 * Number of records currently stored.
	 */
	short numRecords;

	/**
	 * Number of values per record. This does not include timestamp.
	 */
	char valuesPerRecord;

	/**
	 * Uri.
	 */
	char uri[DATABASE_URI_SIZE];
};

#define DATABASE_HEADER_SIZE sizeof(DatabaseHeader)

/**
 * @brief      Entry point for adding data to + updating fixed size files.
 */
class Database
{
private:

	/**
	 * Logger.
	 */
	Logger* _logger;

	/**
	 * AvrClock implementation.
	 */
	AvrClock* _clock;

	/**
	 * Stream to read/write with.
	 */
	AvrStream* _stream;

	/**
	 * Byte offset into stream.
	 */
	int _offset;

	/**
	 * Buffer used internally to move floats around.
	 */
	char _scratchBuffer[4];

	/**
	 * Number of bytes per record. Calculated value.
	 */
	int _bytesPerRecord;

public:

	/**
	 * Header information.
	 */
	DatabaseHeader header;

	/**
	 * @brief      Constructor.
	 * 
	 * @param      clock  The clock implementation to use.
	 */
	Database(AvrClock* clock);

	/**
	 * @brief      Destructor.
	 */
	~Database();

	/**
	 * @brief      Total number of stored records.
	 *
	 * @return     Total number of records stored.
	 */
	float numRecords();

	/**
	 * @brief      Loads header into memory. This is for Databases that already
	 * exist.
	 *
	 * @param      stream  The stream to read/write from.
	 * @param[in]  offset  The byte offset this file starts at.
	 * 
	 * @return     True if the file was successfully loaded.
	 */
	bool load(AvrStream* stream, const int offset);

	/**
	 * @brief      Writes header to disk. This is for new Databases.
	 *
	 * @param      stream  The stream to write to.
	 * @param[in]  offset  The byte offset this file starts at.
	 * @param[in]  contentSize    The size, in bytes, of the file.
	 * @param[in]  valuesPerRecord    The number of values per record.
	 * @param[in]  uri    The uri of the resource.
	 *
	 * @return     True if the file was successfully written.
	 */
	bool init(
		AvrStream* stream,
		const int offset,
		const short contentSize,
		const char valuesPerRecord,
		const char* uri);

	/**
	 * @brief      Flushes any changes to the stream, in case the Database decides
	 * to cache.
	 *
	 * @return     { description_of_the_return_value }
	 */
	bool flush();

	/**
	 * @brief      Adds a set of values to the file. These values are added
	 * with a timestamp.
	 *
	 * @param[in]  value	The floats to add to the file.
	 *
	 * @return     Returns true iff the add was successful.
	 */
	bool add(const float* value);

	/**
	 * @brief      Dumps database data to a buffer. Format is described in more
	 * detail in the core-avr-sensor documentation.
	 * 
	 * This method may modify the buffer and still fail.
	 *
	 * @param[in]  buffer   Buffer to copy records into.
	 * @param[in]  recordOffset  The starting index of records.
	 * @param[in]  recordCount   The number of records to copy into the buffer.
	 *
	 * @return     Returns the number of records copied.
	 */
	int dump(char* buffer, const int recordDffset, const int recordCount);
};

#endif