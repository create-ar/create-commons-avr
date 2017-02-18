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
	Logger* _logger;
	const int _size;
	char* _buffer;
	int _index;

public:
	
	MemoryStreamer(const int size);
	~MemoryStreamer();

	bool init(PinConfiguration pins) override;
	
	virtual char read() override;

	virtual int read(char* const buffer, const int offset, const int count) override;

	virtual bool write(const char value) override;

	virtual bool write(char* const buffer, const int offset, const int count) override;

	virtual int seek(const int offset, const int size) override;
};

#endif