#include "function_pointer_log_target.h"

FunctionPointerLogTarget::FunctionPointerLogTarget(void (*lambda)(const char*))
	:lambda_(lambda)
{
	
}

FunctionPointerLogTarget::~FunctionPointerLogTarget()
{
	//
}

void FunctionPointerLogTarget::log(const char* message)
{
	lambda_(message);
}