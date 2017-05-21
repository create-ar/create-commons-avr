#include "Log.h"

// Scoped to this compilation unit
namespace {
	/**
	 * Supports up to 4 log targets.
	 */
	constexpr int kMaxLogTargets = 4;

	/**
	 * Array of pointers to LogTargets.
	 */
	LogTarget* targets_[kMaxLogTargets];

	/**
	 * Formatter for all logs.
	 */
	LogFormatter* formatter_;

	/**
	 * Tracks loggers.
	 */
	LinkedList<Tuple<const char, Logger>> loggers_;
}


// Methods are global
void Log::setFormatter(LogFormatter* formatter)
{
	formatter_ = formatter;
}

void Log::addTarget(LogTarget* target)
{
	if (nullptr == target)
	{
		return;
	}

	for (int i = 0; i < kMaxLogTargets; i++)
	{
		if (nullptr == targets_[i])
		{
			targets_[i] = target;
			break;
		}
	}
}

void Log::removeTarget(LogTarget* target)
{
	if (nullptr == target)
	{
		return;
	}

	for (int i = 0; i < kMaxLogTargets; i++)
	{
		if (target == targets_[i])
		{
			targets_[i] = nullptr;
			break;
		}
	}
}

void Log::log(const char* level, const char* category, const char* message)
{
	for (int i = 0; i < kMaxLogTargets; i++)
	{
		if (nullptr == targets_[i])
		{
			break;
		}

		if (nullptr == formatter_)
		{
			targets_[i]->log(message);
		}
		else
		{
			targets_[i]->log(formatter_->format(level, category, message));
		}
	}
}

Logger* Log::logger(const char* category)
{
	if (nullptr == category)
	{
		return nullptr;
	}

	Logger* logger = nullptr;

	Iterator<Tuple<const char, Logger>>* it = loggers_.it();
	while (it->moveNext())
	{
		Tuple<const char, Logger>* value = it->current();
		if (value->first == category)
		{
			logger = value->second;
			break;
		}
	}
	delete it;

	if (nullptr == logger)
	{
		logger = new Logger(category);
		loggers_.add(new Tuple<const char, Logger>(
			category,
			logger));
	}

	return logger;
}