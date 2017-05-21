#ifndef ARDUINOCLOCK_HPP
#define ARDUINOCLOCK_HPP

#include "avr_clock.h"

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