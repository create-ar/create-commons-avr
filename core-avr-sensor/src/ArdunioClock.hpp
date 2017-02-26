#ifndef ARDUINOCLOCK_HPP
#define ARDUINOCLOCK_HPP

#include "AvrClock.h"

#include <arduino.h>

/**
 * @brief      Clock implementation for arduino.
 */
class ArduinoClock : public AvrClock
{
public:
	unsigned long time() override
	{
		return millis();
	}
}

#endif