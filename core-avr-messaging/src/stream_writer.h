#ifndef _STREAMWRITER_h
#define _STREAMWRITER_h

#include "converter.h"

class StreamWriter
{
private:
	char* buffer_;
	int buffer_length_;

public:
	int index;

	StreamWriter(const int max_length);
	~StreamWriter();

	char* get_buffer(int* len);

	const void write_short(const short value);
	const void write_int(const int value);
	
	const void write_byte(const char value);
	const void write_bytes(const char* bytes, const short len);

	const void write_bool(const bool value);
};

#endif

