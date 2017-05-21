#ifndef FPLOGTARGET_H
#define FPLOGTARGET_H

#include "LogTarget.h"

/**
 * @brief      Forwards logs to a function pointer.
 */
class FunctionPointerLogTarget : public LogTarget
{

private:
	/**
	 * The function to forward to.
	 */
	void (*lambda_)(const char*);

public:
	/**
	 * @brief      Constructor.
	 *
	 * @param[in]  lambda  The function pointer to push logs to.
	 */
	FunctionPointerLogTarget(void (*lambda)(const char*));

	/**
	 * @brief      Destructor.
	 */
	~FunctionPointerLogTarget();

	/**
	 * @brief      Logs a message.
	 *
	 * @param[in]  message  The message to log.
	 */
	void log(const char* message) override;
};

#endif