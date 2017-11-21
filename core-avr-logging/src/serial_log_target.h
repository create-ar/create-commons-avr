#ifndef SERIALLOGTARGET_H
#define SERIALLOGTARGET_H

#include<Arduino.h>
#include<inttypes.h>

/**
 * @brief      Forwards logs to Arduino Serial interface.
 */
class SerialLogTarget : public LogTarget
{
public:
	/**
	 * @brief      Constructor.
	 */
    SerialLogTarget(int32_t baudRate)
	{
		Serial.begin(baudRate);
	}

    /**
     * @brief      Destructor.
     */
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