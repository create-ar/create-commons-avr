#ifndef SERIALLOGTARGET_H
#define SERIALLOGTARGET_H

#include<Arduino.h>

/**
 * @brief      Forwards logs to Arduino Serial interface.
 */
class SerialLogTarget : public LogTarget
{
public:
    SerialLogTarget() { }
    ~SerialLogTarget() { }

	/**
	 * @brief      Logs a message.
	 *
	 * @param[in]  message  The message to log.
	 */
	virtual void log(const char* message) override
	{
		Serial.println(message);
	}
};

#endif