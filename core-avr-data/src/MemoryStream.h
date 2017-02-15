#include "Stream.h"

#include <Log.h>
#include <Logger.h>

/**
 * @brief      Stream implementation completely in memory.
 */
class MemoryStream : public Stream
{
private:
	Logger* _logger;
	const int _size;
	const char* _buffer;
	int _index;

public:
	MemoryStream();
	~MemoryStream();

	bool init(PinConfiguration pins) override;
	
	virtual char read() override;

	virtual int read(char* const buffer, const int offset, const int count) override;

	virtual bool write(const char value) override;

	virtual bool write(char* const buffer, const int offset, const int count) override;

	virtual int seek(const int offset, const int origin) override;
};