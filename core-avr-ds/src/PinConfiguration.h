#include "LinkedList.h"

enum PinMode
{
	In,
	Out
};

class PinOptions
{
public:
	const char* name;
	int pin;
	PinMode mode;

	PinOptions(
		const char* name,
		int pin,
		PinMode mode)
	{
		this->name = name;
		this->pin = pin;
		this->mode = mode;
	}
};

/**
 * @brief      Configuration options for pins.
 */
class PinConfiguration
{
public:
	/**
	 * Tracks relationship between name and pin.
	 */
	LinkedList<PinOptions> pins;

	PinConfiguration()
	{
		
	}

	~PinConfiguration()
	{
		
	}

	PinOptions* pin(const char* name)
	{
		auto it = pins.it();
		while (it->current() != nullptr)
		{
			auto config = it->current();
			if (config->name == name)
			{
				return config;
			}

			it->moveNext();
		}

		return nullptr;
	}
};