#ifndef AVRCLOCK_H
#define AVRCLOCK_H

#include <inttypes.h>

/**
 * @brief      Abstraction for clock.
 */
class AvrClock
{
public:
	/**
	 * @brief      Virtual destructor.
	 */
	virtual ~AvrClock()
	{
		//
	}

	/**
	 * @brief      Returns the total number of milliseconds since the start of
	 * the program.
	 *
	 * @return     Total number of milliseconds since the start of the program.
	 */
	virtual uint32_t now() = 0;
};

#endif