#ifndef EEPROMSTREAM_H
#define EEPROMSTREAM_H

#include "avr_stream.h"

#include <pin_configuration.h>

/**
 * @brief      Abstracts SPI + EEPROM paging into working with a single
 * block of contiguous bytes. All calls are blocking.
 */
class EEPROMStream : public AvrStream
{
private:
	
	/**
	 * Number of bytes per page.
	 */
	uint pageSize_;

	/**
	 * Total number of pages.
	 */
	uint numPages_;

public:
	/**
	 * @brief      Constructor.
	 */
	EEPROMStream(uint pageSize, uint numPages);

	/**
	 * @brief      Destructor.
	 */
	~EEPROMStream();

	/**
	 * @brief      Initializes the stream with pin info.
	 *
	 * @param[in]  pins      The configuration for each pin.
	 */
	bool init(PinConfiguration pins);

	virtual char read() override;

	virtual int read(char* const buffer, const int offset, const int count) override;

	virtual bool write(const char value) override;

	virtual int write(char* const buffer, const int offset, const int count) override;

	virtual int set(const char value, const int offset, const int count) override;

	virtual int seek(const int offset, const int origin) override;
};

#endif