#ifndef MEMORYSTREAM_H
#define MEMORYSTREAM_H

#include "Streamer.h"

#include <Log.h>
#include <Logger.h>

/**
 * @brief      Streamer implementation completely in memory.
 */
class MemoryStreamer : public Streamer
{
private:
	/**
	 * Logger instance.
	 */
	Logger* _logger;

	/**
	 * Size of the buffer.
	 */
	const int _size;

	/**
	 * Actual memory buffer.
	 */
	char* _buffer;

	/**
	 * Index in the buffer.
	 */
	int _index;

	/**
	 * @brief      Calculates the index given an offset and a count.
	 *
	 * @param[in]  offset  The offset at which to start the index.
	 * @param[in]  count   The count to advance the index.
	 *
	 * @return     For bad inputs, outputs -1. For all other inputs, returns
	 * clamped values.
	 */
	int index(const int offset, const int count);

public:
	
	MemoryStreamer(const int size);
	~MemoryStreamer();

	bool init(PinConfiguration pins) override;
	
	virtual char read() override;

	virtual int read(char* const buffer, const int offset, const int count) override;

	virtual bool write(const char value) override;

	virtual int write(char* const buffer, const int offset, const int count) override;

	virtual int seek(const int offset, const int count) override;
};

#endif