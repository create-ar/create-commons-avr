/**
 * @brief      Abstracts SPI + EEPROM paging into working with a single
 * block of contiguous bytes. All calls are blocking.
 */
class EEPROMStream
{
public:
	/**
	 * @brief      Reads a single byte from the stream and advances the index.
	 *
	 * @return     Returns the byte read.
	 */
	char read();

	/**
	 * @brief      Reads a block of bytes into the input buffer.
	 *
	 * @param      buffer  The buffer to read values into.
	 * @param[in]  offset  The starting index.
	 * @param[in]  count   The maximum number of bytes to read.
	 *
	 * @return     The number of bytes actually read.
	 */
	int read(char* buffer, const int offset, const int count);

	/**
	 * @brief      Writes a single byte to the stream and advances the index.
	 *
	 * @param[in]  value  The value to write.
	 *
	 * @return     Returns true if the byte could be successfully written.
	 */
	bool write(const char value);

	/**
	 * @brief      Writes a block of bytes to the stream.
	 *
	 * @param[in]  buffer  The buffer to copy values from.
	 * @param[in]  offset  The starting byte offset.
	 * @param[in]  count   The number of bytes to read from buffer.
	 *
	 * @return     Returns true if the write was successful.
	 */
	bool write(const char* buffer, const int offset, const int count);

	/**
	 * @brief      Moves the index to a specific place. This is used when
	 * reading and writing single values.
	 *
	 * @param[in]  offset  The offset to count from.
	 * @param[in]  origin  The number of bytes to add to the offset.
	 *
	 * @return     The current absolute index.
	 */
	int seek(const int offset, const int origin);
};