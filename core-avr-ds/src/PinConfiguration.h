#ifndef PINCONFIGURATION_H
#define PINCONFIGURATION_H

#include "LinkedList.h"

/**
 * @brief      Potential modes of a pin.
 */
enum PinMode
{
	In,
	Out
};

/**
 * @brief      Contains all potential options for a pin.
 */
class PinOptions
{
public:
	/**
	 * Name of the pin.
	 */
	const char* name;

	/**
	 * Pin id. Maps to Arduino pinout.
	 */
	int pin;

	/**
	 * Mode this pin should function.
	 */
	PinMode mode;

	/**
	 * @brief      Constructor.
	 *
	 * @param[in]  name  The name
	 * @param[in]  pin   The pin
	 * @param[in]  mode  The mode
	 */
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
private:
	/**
	 * Tracks relationship between name and pin.
	 */
	LinkedList<PinOptions> _pins;

public:
	/**
	 * @brief      Constructor.
	 */
	PinConfiguration()
	{
		
	}

	/**
	 * @brief      Destructor.
	 */
	~PinConfiguration()
	{
		Iterator<PinOptions>* it = _pins.it();
		while (it->moveNext())
		{
			delete it->current();
		}

		delete it;
	}

	/**
	 * @brief      Adds a pin to the list.
	 *
	 * @param[in]  name  The name of the pin. Must be unique.
	 * @param[in]  pin   The pin number.
	 * @param[in]  mode  The mode of this pin.
	 *
	 * @return     A this pointer.
	 */
	PinConfiguration* add(
		const char* name,
		int pin,
		PinMode mode)
	{
		PinOptions* existing = getPin(name);
		if (nullptr == existing)
		{
			_pins.add(new PinOptions(name, pin, mode));
		}

		return this;
	}

	/**
	 * @brief      Retrieves options for a pin by name.
	 *
	 * @param[in]  name  The name of the pin.
	 *
	 * @return     The associated PinOptions or nullptr.
	 */
	PinOptions* getPin(const char* name)
	{
		PinOptions* options = nullptr;

		Iterator<PinOptions>* it = _pins.it();
		while (it->current() != nullptr)
		{
			PinOptions* config = it->current();
			if (config->name == name)
			{
				options = config;
				break;
			}

			it->moveNext();
		}

		delete it;

		return options;
	}
};

#endif