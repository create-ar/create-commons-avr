#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "avr_stream.h"

#include <log.h>
#include <logger.h>

/**
 * @brief      Stream implementation completely in memory.
 */
class MemoryStream : public AvrStream
{
private:
	/**
	 * Logger instance.
	 */
	Logger* logger_;

	/**
	 * Size of the buffer.
	 */
	const int32_t size_;

	/**
	 * Actual memory buffer.
	 */
	char* buffer_;

	/**
	 * Index in the buffer.
	 */
	int32_t index_;

public:
	
	MemoryStream(const int32_t size);
	~MemoryStream();

	virtual char read() override;

	virtual int32_t read(char* const buffer, const int32_t offset, const int32_t count) override;

	virtual bool write(const char value) override;

	virtual int32_t write(char* const buffer, const int32_t offset, const int32_t count) override;

	virtual int32_t set(const char value, const int32_t offset, const int32_t count) override;

	virtual int32_t seek(const int32_t offset, const int32_t count) override;
};

#endif