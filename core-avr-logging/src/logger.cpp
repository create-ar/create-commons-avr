#include "logger.h"
#include "log.h"

Logger::Logger(const char* category)
	: category_(category)
{
	
}

Logger::~Logger() { }

void Logger::debug(const char* message)
{
	Log::log("debug", category_, message);
}

void Logger::info(const char* message)
{
	Log::log("info", category_, message);
}

void Logger::warn(const char* message)
{
	Log::log("warn", category_, message);
}

void Logger::error(const char* message)
{
	Log::log("error", category_, message);
}