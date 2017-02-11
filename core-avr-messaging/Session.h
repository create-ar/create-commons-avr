#ifndef SESSION_h
#define SESSION_h

// abstract class for a session
class Session
{
public:
	// true if there are bytes available
	virtual bool available() = 0;

	// writes a buffer
	virtual void write(const unsigned char* buffer, const int size) = 0;

	// reads a single char
	virtual char read() = 0;
};
#endif