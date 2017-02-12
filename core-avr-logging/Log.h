#ifndef LOG_H
#define LOG_H

#include "LogTarget.h"
#include "LogFormatter.h"

/**
 * @brief      Static interface for logging.
 */
class Log
{
private:
	/**
	 * Supports up to 4 log targets.
	 */
	#define MAX_LOGTARGETS 4

	/**
	 * Array of pointers to LogTargets.
	 */
	static LogTarget* _targets[MAX_LOGTARGETS];

	/**
	 * Formatter for all logs.
	 */
	static LogFormatter* _formatter;

public:
	/**
	 * @brief      Sets the formatter for logs.
	 *
	 * @param      formatter  The formatter.
	 */
	static void setFormatter(LogFormatter* formatter);

	/**
	 * @brief      Adds a target to receive logs.
	 *
	 * @param      target  The target.
	 */
	static void addTarget(LogTarget* target);

	/**
	 * @brief      Removes a target from receiving logs.
	 *
	 * @param      target  The target.
	 */
	static void removeTarget(LogTarget* target);

	/**
	 * @brief      Log!
	 *
	 * @param[in]  level     The level of the log.
	 * @param[in]  category  The category of the log.
	 * @param[in]  message   The message to log.
	 */
	static void log(const char* level, const char* category, const char* message);
};

#endif