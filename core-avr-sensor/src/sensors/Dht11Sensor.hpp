#include "../Sensor.h"

#include <Dht11.h>

class Dht11Sensor : public Sensor
{
private:
	Dht11* _dht11;

public:
	Dht11Sensor() :
		_dht11(nullptr)
	{
		//
	}

	~Dht11Sensor()
	{
		if (nullptr != _dht11)
		{
			delete _dht11;
		}
	}

	bool init(SensorConfig config) override
	{
		bool valid = Sensor::init(config);
		if (!valid)
		{
			return false;
		}


	}

	bool poll(const float* values) override
	{

	}
};