#include "Log.h"

void Log::setFormatter(LogFormatter* formatter)
{
	_formatter = formatter;
}

void Log::addTarget(LogTarget* target)
{
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

		_targets[i]->log(_formatter->format(level, category, message));
	}
}

Logger* Log::logger(const char* category)
{
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