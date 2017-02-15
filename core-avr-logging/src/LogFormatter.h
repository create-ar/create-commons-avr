#ifndef LOGFORMATTER_H
#define LOGFORMATTER_H

/**
 * @brief      Formats logs.
 */
class LogFormatter
{
public:
	/**
	 * @brief      Destructor.
	 */
	virtual ~LogFormatter() = 0;

	/**
	 * @brief      Formats a log.
	 *
	 * @param[in]  level     The level of the log.
	 * @param[in]  category  The category of the log.
	 * @param[in]  message   The message.
	 *
	 * @return     The formatted log.
	 */
	virtual const char* format(
		const char* level,
		const char* category,
		const char* message) = 0;
};

/**
 * @brief      Destructor.
 */
inline LogFormatter::~LogFormatter()
{
	//
}

#endif