#include "log_formatter.h"

class DummyFormatter : public LogFormatter
{
public:
	const char* level;
	const char* category;
	const char* message;

	const char* staticMessage;

	DummyFormatter(const char* staticMessage)
	{
		this->staticMessage = staticMessage;
	}

	const char* format(
		const char* level,
		const char* category,
		const char* message) override
	{
		this->level = level;
		this->category = category;
		this-> message = message;

		return staticMessage;
	}
};