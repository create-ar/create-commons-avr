#ifndef	AVRSTREAM_H
#define AVRSTREAM_H

#include <inttypes.h>

/**
 * @brief      Abstracts the method of reading/writing bytes.
 */
class AvrStream
{
public:
	AvrStream()
	{

	}

	virtual ~AvrStream()
	{

	}

	/**
	 * @brief      Returns the index of the stream.
	 * 
	 * @return     The current index.	
	 */
	virtual int32_t get_index() = 0;

	/**
	 * @brief      Reads a single byte from the stream and advances the index.
	 *
	 * @return     Returns the byte read.
	 */
	virtual char read() = 0;

	/**
	 * @brief      Reads a block of bytes into the input buffer.
	 *
	 * @param      buffer  The buffer to read values into.
	 * @param[in]  offset  The starting index.
	 * @param[in]  count   The maximum number of bytes to read.
	 *
	 * @return     The number of bytes actually read. -1 if there was an error.
	 */
	virtual int32_t read(unsigned char* const buffer, const int32_t offset, const int32_t count) = 0;

	/**
	 * @brief      Writes a single byte to the stream and advances the index.
	 *
	 * @param[in]  value  The value to write.
	 *
	 * @return     Returns true if the byte could be successfully written.
	 */
	virtual bool write(const unsigned char value) = 0;

	/**
	 * @brief      Writes a block of bytes to the stream.
	 *
	 * @param[in]  buffer  The buffer to copy values from.
	 * @param[in]  offset  The starting byte offset.
	 * @param[in]  count   The number of bytes to write from buffer.
	 *
	 * @return     Returns how many bytes were successfully written.
	 */
	virtual int32_t write(unsigned char* const buffer, const int32_t offset, const int32_t count) = 0;

	/**
	 * @brief      Sets a block of bytes to a specific value. Effectively, memset.
	 *
	 * @param[in]  value   The value to fill with.
	 * @param[in]  offset  The starting byte offset.
	 * @param[in]  count   The number of bytes to set.
	 *
	 * @return     Returns how many bytes were successfully set.
	 */
	virtual int32_t set(const unsigned char value, const int32_t offset, const int32_t count) = 0;

	/**
	 * @brief      Moves the index to a specific place. This is used when
	 * reading and writing single values.
	 *
	 * @param[in]  offset  The offset to count from.
	 * @param[in]  origin  The number of bytes to add to the offset.
	 *
	 * @return     The current absolute index.
	 */
	virtual int32_t seek(const int32_t offset, const int32_t origin) = 0;
};

#endif