#ifndef LOGTARGET_H
#define LOGTARGET_H

/**
 * @brief      Pure virtual base class that describes the LogTarget interface.
 */
class LogTarget
{
public:
	/**
	 * @brief      Logs a message.
	 *
	 * @param[in]  message  The message to log.
	 */
	virtual void log(const char* message) = 0;
};

#endif