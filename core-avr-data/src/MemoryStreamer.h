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

public:
	
	MemoryStreamer(const int size);
	~MemoryStreamer();

	bool init(PinConfiguration pins) override;
	
	virtual char read() override;

	virtual int read(char* const buffer, const int offset, const int count) override;

	virtual bool write(const char value) override;

	virtual int write(char* const buffer, const int offset, const int count) override;

	virtual int set(const char value, const int offset, const int count) override;

	virtual int seek(const int offset, const int count) override;
};

#endif