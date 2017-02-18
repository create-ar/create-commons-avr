#ifndef FPLOGTARGET_H
#define FPLOGTARGET_H

#include "LogTarget.h"

class FunctionPointerLogTarget : public LogTarget
{

private:
	void (*_lambda)(const char*);

public:
	FunctionPointerLogTarget(void (*lambda)(const char*));
	~FunctionPointerLogTarget();

	void log(const char* message) override;
};

#endif