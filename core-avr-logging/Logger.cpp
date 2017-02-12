#include "Logger.h"
#include "Log.h"

Logger::Logger(char* category)
{
	_category = category;
}

void Logger::debug(const char* message)
{
	Log::log("debug", message);
}

void Logger::info(const char* message)
{
	Log::log("info", message);
}

void Logger::warn(const char* message)
{
	Log::log("warn", message);
}

void Logger::error(const char* message)
{
	Log::log("error", message);
}