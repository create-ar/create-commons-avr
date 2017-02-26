#include "Dht11Sensor.h"


float Dht11Sensor::dewPoint(double celsius, double humidity)
{
	// (1) Saturation Vapor Pressure = ESGG(T)
	double RATIO = 373.15 / (273.15 + celsius);
	double RHS = -7.90298 * (RATIO - 1);
	RHS += 5.02808 * log10(RATIO);
	RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / RATIO))) - 1);
	RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1);
	RHS += log10(1013.246);

	// factor -3 is to adjust units - Vapor Pressure SVP * humidity
	double VP = pow(10, RHS - 3) * humidity;

	// (2) DEWPOINT = F(Vapor Pressure)
	double T = log(VP / 0.61078);   // temp var
	return (241.88 * T) / (17.558 - T);
}

Dht11Sensor::Dht11Sensor() :
	_dht11(nullptr)
{
	_logger = Log::logger("DHT11");
}

Dht11Sensor::~Dht11Sensor()
{
	if (nullptr != _dht11)
	{
		delete _dht11;
	}
}

bool Dht11Sensor::init(SensorConfig config) override
{
	bool valid = Sensor::init(config);
	if (!valid)
	{
		return false;
	}

	if (config.numValues > DHT11_NUM_VALUES)
	{
		_logger->error("Invalid config: Cannot initialize DHT11 with more than 3 values.");
		return false;
	}

	const PinOptions* pin = _pins->pin(DHT11_PIN_NAME);
	if (nullptr == pin)
	{
		_logger->error("Invalid config: Cannot initialize DHT11 with no pins.");
		return false;
	}

	_dht11 = new Dht11(pin->pin);

	return true;
}

bool Dht11Sensor::poll(const float* values) override
{
	switch (_dht11->read())
	{
		// read values
		case Dht11::OK:
		{
			values[0] = _dht11->getTemperature();

			if (config.numValues > 1)
			{
				values[1] = _dht11->getHumidity();

				if (config.numValues > 2)
				{
					values[2] = dewpoint(values[0], values[1]);
				}
			}

			return true;
		}
		// error cases
		case Dht11::ERROR_CHECKSUM:
		{
			_logger->error("Bad checksum.");

			return false;
		}
		case Dht11::ERROR_TIMEOUT:
		{
			_logger->error("Timeout.");

			return false;
		}
		default:
		{
			_logger->error("Unknown error.");

			return false;
		}
	}
	
	return false;
}