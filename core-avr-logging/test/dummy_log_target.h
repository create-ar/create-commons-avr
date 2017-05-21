#include "log_target.h"

class DummyLogTarget : public LogTarget
{
public:
	const char* lastMessage;

	void log(const char* message) override
	{
		lastMessage = message;
	}
};