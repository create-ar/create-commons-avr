#ifndef CONSOLELOGTARGET_H
#define CONSOLELOGTARGET_H

#include "LogTarget.h"

/**
 * @brief      Forwards logs to stdout.
 */
class ConsoleLogTarget : public LogTarget
{
public:

	/**
	 * @brief      Constructor.
	 */
	ConsoleLogTarget();

	/**
	 * @brief      Destructor.
	 */
	~ConsoleLogTarget();

	/**
	 * @brief      Log function.
	 *
	 * @param[in]  message  The message to log.
	 */
	void log(const char* message) override;
};

#endif