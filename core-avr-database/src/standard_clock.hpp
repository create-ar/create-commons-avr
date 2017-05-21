#ifndef STANDARDCLOCK_H
#define STANDARDCLOCK_H

#include "avr_clock.h"

#include <time.h>

/**
 * @brief      std implementation of AvrClock. This is used for testing.
 */
class StandardClock : public AvrClock
{
private:
	/**
	 * Time object was created.
	 */
	time_t startTime_;

public:
	/**
	 * @brief      Constructor.
	 */
	StandardClock()
	{
		startTime_ = time(nullptr);
	}

	/**
	 * @brief      Gets the current time.
	 *
	 * @return     Returns the time.
	 */
	unsigned long now() override
	{
		time_t now = time(0);
		return (unsigned long) ((now - startTime_) * 1000);
	}
};

#endif