// StreamWriter.h

#ifndef _STREAMWRITER_h
#define _STREAMWRITER_h

class StreamWriter
{
private:
	unsigned char* _buffer;
	int _bufferLen;

public:
	int index;

	StreamWriter(const int maxLen);
	~StreamWriter();

	unsigned char* getBuffer(int* len);

	const void writeShort(const short value);
	const void writeInt(const int value);
	
	const void writeByte(const unsigned char value);
	const void writeBytes(const unsigned char* bytes, const short len);
	const void writeIntAsByte(const int value);

	const void writeBool(const bool value);
};

#endif

