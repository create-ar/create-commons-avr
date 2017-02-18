#ifndef CONSOLELOGTARGET_H
#define CONSOLELOGTARGET_H

#include "LogTarget.h"

class ConsoleLogTarget : public LogTarget
{
public:

	ConsoleLogTarget();
	~ConsoleLogTarget();

	void log(const char* message) override;
};

#endif