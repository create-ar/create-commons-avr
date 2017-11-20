#ifndef _STREAMWRITER_h
#define _STREAMWRITER_h

#include "avr_stream.h"
#include <inttypes.h>

class StreamWriter
{
private:
	AvrStream* stream_;

public:
	StreamWriter();
	
	void set_stream(AvrStream* stream);
	AvrStream* get_stream();

	const void write_short(const int16_t value);
	const void write_int(const int32_t value);
	
	const void write_byte(const char value);
	const void write_bytes(char* const bytes, const int16_t len);

	const void write_bool(const bool value);
};

#endif

