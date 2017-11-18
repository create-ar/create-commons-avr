#ifndef DATABASE_H
#define DATABASE_H

#include "avr_stream.h"
#include "avr_clock.h"

#include <string.h>
#include <logger.h>

#define DATABASE_URI_SIZE 64

/**
 * @brief      Description of file, stored at the start of the file buffer.
 */
struct DatabaseHeader
{
	/**
	 * Version of the file.
	 */
	int32_t version;

	/**
	 * Number of bytes, excluding the header.
	 */
	int16_t contentSize;

	/**
	 * Number of records currently stored.
	 */
	int16_t numRecords;

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
	Logger* logger_;

	/**
	 * AvrClock implementation.
	 */
	AvrClock* clock_;

	/**
	 * Stream to read/write with.
	 */
	AvrStream* stream_;

	/**
	 * Byte offset into stream.
	 */
	int32_t offset_;

	/**
	 * Number of bytes per record. Calculated value.
	 */
	int32_t bytesPerRecord_;

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
	bool load(AvrStream* stream, const int32_t offset);

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
		const int32_t offset,
		const int16_t contentSize,
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
	int32_t dump(char* buffer, const int32_t recordOffset, const int32_t recordCount);
};

#endif
