#include "Logger.h"
#include "Log.h"

Logger::Logger(const char* category)
{
	_category = category;
}

Logger::~Logger() { }

void Logger::debug(const char* message)
{
	Log::log("debug", _category, message);
}

void Logger::info(const char* message)
{
	Log::log("info", _category, message);
}

void Logger::warn(const char* message)
{
	Log::log("warn", _category, message);
}

void Logger::error(const char* message)
{
	Log::log("error", _category, message);
}