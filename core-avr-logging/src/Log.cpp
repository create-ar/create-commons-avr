#include "Log.h"

// Scoped to this compilation unit
namespace {
	/**
	 * Supports up to 4 log targets.
	 */
	constexpr int MAX_LOGTARGETS = 4;

	/**
	 * Array of pointers to LogTargets.
	 */
	LogTarget* _targets[MAX_LOGTARGETS];

	/**
	 * Formatter for all logs.
	 */
	LogFormatter* _formatter;

	/**
	 * Tracks loggers.
	 */
	LinkedList<Tuple<const char, Logger>> _loggers;
}


// Methods are global
void Log::setFormatter(LogFormatter* formatter)
{
	_formatter = formatter;
}

void Log::addTarget(LogTarget* target)
{
	if (nullptr == target)
	{
		return;
	}

	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (nullptr == _targets[i])
		{
			_targets[i] = target;
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

	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (target == _targets[i])
		{
			_targets[i] = nullptr;
			break;
		}
	}
}

void Log::log(const char* level, const char* category, const char* message)
{
	for (int i = 0; i < MAX_LOGTARGETS; i++)
	{
		if (nullptr == _targets[i])
		{
			break;
		}

		if (nullptr == _formatter)
		{
			_targets[i]->log(message);
		}
		else
		{
			_targets[i]->log(_formatter->format(level, category, message));
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

	LinkedListIterator<Tuple<const char, Logger>>* it = _loggers.it();
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
		_loggers.add(new Tuple<const char, Logger>(
			category,
			logger));
	}

	return logger;
}