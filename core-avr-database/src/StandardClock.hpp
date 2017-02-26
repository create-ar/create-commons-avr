#ifndef STANDARDCLOCK_H
#define STANDARDCLOCK_H

#include "AvrClock.h"

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
	time_t _startTime;

public:
	/**
	 * @brief      Constructor.
	 */
	StandardClock()
	{
		_startTime = time(nullptr);
	}

	/**
	 * @brief      Gets the current time.
	 *
	 * @return     Returns the time.
	 */
	unsigned long now() override
	{
		time_t now = time(0);
		return (unsigned long) ((now - _startTime) * 1000);
	}
};

#endif