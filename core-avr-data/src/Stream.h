#ifndef	STREAM_H
#define STREAM_H

#include <PinConfiguration.h>

/**
 * @brief      Abstracts the method of reading/writing bytes.
 */
class Stream
{
public:
	/**
	 * @brief      Constructor.
	 */
	Stream();

	/**
	 * @brief      Destructor.
	 */
	~Stream();

	/**
	 * @brief      Initializes the stream with pin info.
	 * 
	 * @param[in]  pins      The configuration for pins.
	 */
	virtual bool init(PinConfiguration pins) = 0;

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
	 * @return     The number of bytes actually read.
	 */
	virtual int read(char* const buffer, const int offset, const int count) = 0;

	/**
	 * @brief      Writes a single byte to the stream and advances the index.
	 *
	 * @param[in]  value  The value to write.
	 *
	 * @return     Returns true if the byte could be successfully written.
	 */
	virtual bool write(const char value) = 0;

	/**
	 * @brief      Writes a block of bytes to the stream.
	 *
	 * @param[in]  buffer  The buffer to copy values from.
	 * @param[in]  offset  The starting byte offset.
	 * @param[in]  count   The number of bytes to write from buffer.
	 *
	 * @return     Returns true if the write was successful.
	 */
	virtual bool write(char* const buffer, const int offset, const int count) = 0;

	/**
	 * @brief      Moves the index to a specific place. This is used when
	 * reading and writing single values.
	 *
	 * @param[in]  offset  The offset to count from.
	 * @param[in]  origin  The number of bytes to add to the offset.
	 *
	 * @return     The current absolute index.
	 */
	virtual int seek(const int offset, const int origin) = 0;
};

/**
 * @brief      Destructor.
 */
inline Stream::~Stream()
{
	//
}

#endif