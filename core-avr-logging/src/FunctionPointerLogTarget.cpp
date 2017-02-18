#include "FunctionPointerLogTarget.h"

FunctionPointerLogTarget::FunctionPointerLogTarget(void (*lambda)(const char*))
{
	_lambda = lambda;
}

FunctionPointerLogTarget::~FunctionPointerLogTarget()
{
	//
}

void FunctionPointerLogTarget::log(const char* message)
{
	_lambda(message);
}