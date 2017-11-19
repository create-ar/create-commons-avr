#ifndef _STREAMREADER_h
#define _STREAMREADER_h

class StreamReader
{
private:
	char* buffer_;
	int buffer_length_;
	int index_;

public:
	StreamReader();

	char* get_buffer();

	void set_buffer(
		char* buffer,
		int length,
		int index);

	int get_index();

	void set_index(int index);

	short read_short();

	int read_int();
	
	char read_byte();

	char* read_bytes(short& len);

	bool read_bool();
};

#endif

