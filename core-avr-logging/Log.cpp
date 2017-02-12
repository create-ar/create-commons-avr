#include "Log.h"

/**
 * @brief      Sets the formatter for logs.
 *
 * @param      formatter  The formatter.
 */
void Log::setFormatter(LogFormatter* formatter)
{
	_formatter = formatter;
}

/**
 * @brief      Adds a target to receive logs.
 *
 * @param      target  The target.
 */
static void addTarget(LogTarget* target)
{
	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (nullptr == _target[i])
		{
			_target[i] = target;
			break;
		}
	}
}

/**
 * @brief      Removes a target from receiving logs.
 *
 * @param      target  The target.
 */
static void removeTarget(LogTarget* target)
{
	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (target == _target[i])
		{
			_target[i] = nullptr;
			break;
		}
	}
}

/**
 * @brief      Log!
 *
 * @param[in]  level     The level of the log.
 * @param[in]  category  The category of the log.
 * @param[in]  message   The message to log.
 */
static void log(const char* level, const char* category, const char* message)
{
	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (nullptr == _target[i])
		{
			break;
		}

		_target[i]->log(_formatter->format(level, category, message));
	}
}