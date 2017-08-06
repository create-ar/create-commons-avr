#ifndef DEFAULTFORMATTER_H
#define DEFAULTFORMATTER_H

#include "log_formatter.h"

#include <string.h>

/**
 * @brief      Formats a log.
 */
class DefaultFormatter : public LogFormatter
{
public:
	/**
	 * True iff the time should be appended to the log.
	 */
	bool time;

	/**
	 * @brief      Default constructor.
	 */
	DefaultFormatter() : time(true)
	{

	}

	/**
	 * @brief      Default destructor.
	 */
	~DefaultFormatter()
	{

	}

	/**
	 * @brief      Formats a log.
	 *
	 * @param[in]  level     The level of the log.
	 * @param[in]  category  The category of the log.
	 * @param[in]  message   The message to log.
	 *
	 * @return     The formatted log.
	 */
	const char* format(
		const char* level,
		const char* category,
		const char* message) override
	{
		int size;

		static char defaultString[] = "NULL";

		const char* levelBuffer = nullptr == level ? defaultString : level;
		const char* categoryBuffer = nullptr == category ? defaultString : category;
		const char* messageBuffer = nullptr == message ? defaultString : message;

		// [{level}][{category}]\s{message}
		char* buffer = new char[
			strlen(levelBuffer) + 2
			+ strlen(categoryBuffer) + 2
			+ strlen(messageBuffer) + 2];
		
		sprintf(buffer, "[%s][%s] %s", levelBuffer, categoryBuffer, messageBuffer);

		return (const char*) buffer;
	}
};

#endif