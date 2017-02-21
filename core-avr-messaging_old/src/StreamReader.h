// StreamReader.h

#ifndef _STREAMREADER_h
#define _STREAMREADER_h

class StreamReader
{
private:
	unsigned char* _buffer;
	int _bufferLength;
	int _index;

public:
	StreamReader();

	unsigned char* getBuffer();
	void setBuffer(
		unsigned char* buffer,
		int length,
		int index);
	int getIndex();
	void setIndex(int index);

	short readShort();
	int readInt();
	
	unsigned char readByte();
	void readBytes(unsigned char* value, short& len);
	int readByteAsInt();

	bool readBool();
};

#endif

