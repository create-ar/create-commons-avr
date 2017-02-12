#ifndef SERIALLOGTARGET_H
#define SERIALLOGTARGET

#include<Arduino.h>

/**
 * @brief      Forwards logs to Arduino Serial interface.
 */
class SerialLogTarget : public LogTarget
{
public:
	/**
	 * @brief      Logs a message.
	 *
	 * @param[in]  message  The message to log.
	 */
	virtual void log(const char* message)
	{
		Serial.println(message);
	}
};

#endif