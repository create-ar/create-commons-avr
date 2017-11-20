#ifndef EEPROMSTREAM_H
#define EEPROMSTREAM_H

#include "avr_stream.h"

#include <pin_configuration.h>

/**
 * @brief      Abstracts SPI + EEPROM paging int32_to working with a single
 * block of contiguous bytes. All calls are blocking.
 */
class EEPROMStream : public AvrStream
{
private:
	
	/**
	 * Number of bytes per page.
	 */
	uint32_t pageSize_;

	/**
	 * Total number of pages.
	 */
	uint32_t numPages_;

public:
	/**
	 * @brief      Constructor.
	 */
	EEPROMStream(uint32_t pageSize, uint32_t numPages);

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

	virtual int32_t get_index() override;

	virtual char read() override;

	virtual int32_t read(char* const buffer, const int32_t offset, const int32_t count) override;

	virtual bool write(const char value) override;

	virtual int32_t write(char* const buffer, const int32_t offset, const int32_t count) override;

	virtual int32_t set(const char value, const int32_t offset, const int32_t count) override;

	virtual int32_t seek(const int32_t offset, const int32_t origin) override;
};

#endif