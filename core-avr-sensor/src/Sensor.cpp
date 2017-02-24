#include "Sensor.h"

SensorConfig Sensor::config()
{
	return _config;
}

bool Sensor::init(SensorConfig config)
{
	_config = config;

	return true;
}