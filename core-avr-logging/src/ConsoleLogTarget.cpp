#include "ConsoleLogTarget.h"

#include <stdio.h>

ConsoleLogTarget::ConsoleLogTarget()
{
	//
}

ConsoleLogTarget::~ConsoleLogTarget()
{
	//
}

void ConsoleLogTarget::log(const char* message)
{
	printf("%s", message);
}