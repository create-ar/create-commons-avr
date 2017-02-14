#ifndef DEFAULTFORMATTER_H
#define DEFAULTFORMATTER_H

#include "LogFormatter.h"

/**
 * @brief      Formats a log.
 */
class DefaultFormatter : public LogFormatter
{
public:
	/**
	 * True iff the time should be appended to the log.
	 */
	bool time = true;

	/**
	 * @brief      Formats a log.
	 *
	 * @param[in]  level     The level of the log.
	 * @param[in]  category  The category of the log.
	 * @param[in]  message   The message to log.
	 *
	 * @return     The formatted log.
	 */
	virtual const char* format(
		const char* level,
		const char* category,
		const char* message)
	{
		return message;
		/*return "[" + level + "]"
			+ "[" + category + "]"
			//+ (time ? ("[" + millis() + "]\t") : "\t")
			+ message;*/
	}
};

#endif