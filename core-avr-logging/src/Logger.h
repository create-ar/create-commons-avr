#ifndef LOGGER_H
#define LOGGER_H

/**
 * @brief      Logger instance.
 */
class Logger
{
private:
	/**
	 * The category with which to prefix logs.
	 */
	const char* _category;

public:
	/**
	 * @brief      New logger of a specific category.
	 *
	 * @param      category  The category to prefix logs with.
	 */
	Logger(const char* category);

	~Logger();

	/**
	 * @brief      Logs at a debug level.
	 *
	 * @param[in]  message  The message to log.
	 */
	void debug(const char* message);

	/**
	 * @brief      Logs at an info level.
	 *
	 * @param[in]  message  The message to log.
	 */
	void info(const char* message);

	/**
	 * @brief      Logs at a warn level.
	 *
	 * @param[in]  message  The message to log.
	 */
	void warn(const char* message);

	/**
	 * @brief      Logs at an error level.
	 *
	 * @param[in]  message  The message to log.
	 */
	void error(const char* message);
};

#endif