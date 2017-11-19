#ifndef _STREAMREADER_h
#define _STREAMREADER_h

class StreamReader
{
private:
	unsigned char* buffer_;
	int buffer_length_;
	int index_;

public:
	StreamReader();

	unsigned char* get_buffer();

	void set_buffer(
		unsigned char* buffer,
		int length,
		int index);

	int get_index();

	void set_index(int index);

	short read_short();

	int read_int();
	
	unsigned char read_byte();

	void read_bytes(unsigned char* value, short& len);

	bool read_bool();
};

#endif

