#ifndef _STREAMREADER_h
#define _STREAMREADER_h

#include <inttypes.h>

#include "avr_stream.h"

class StreamReader
{
private:
	AvrStream* stream_;

public:
	StreamReader();

	void set_stream(AvrStream* stream);
	AvrStream* get_stream();

	int16_t read_short();

	int32_t read_int();
	
	char read_byte();

	char* read_bytes();

	bool read_bool();
};

#endif