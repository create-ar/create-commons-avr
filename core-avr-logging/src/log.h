#ifndef LOG_H
#define LOG_H

#include "log_target.h"
#include "log_formatter.h"
#include "logger.h"
#include "linked_list.h"
#include "tuple.h"

namespace Log {
	
	/**
	 * @brief      Sets the formatter for logs.
	 *
	 * @param      formatter  The formatter.
	 */
	extern void setFormatter(LogFormatter* formatter);

	/**
	 * @brief      Adds a target to receive logs.
	 *
	 * @param      target  The target.
	 */
	extern void addTarget(LogTarget* target);

	/**
	 * @brief      Removes a target from receiving logs.
	 *
	 * @param      target  The target.
	 */
	extern void removeTarget(LogTarget* target);

	/**
	 * @brief      Log!
	 *
	 * @param[in]  level     The level of the log.
	 * @param[in]  category  The category of the log.
	 * @param[in]  message   The message to log.
	 */
	extern void log(const char* level, const char* category, const char* message);

	/**
	 * @brief      Retrieves a logger for a category. If a logger already
	 * exists, it returns that logger.
	 *
	 * @param[in]  category  The category. Can be anything.
	 *
	 * @return     A logger.
	 */
	extern Logger* logger(const char* category);
};

#endif