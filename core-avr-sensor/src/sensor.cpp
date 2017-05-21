#include "Sensor.h"

SensorConfig Sensor::config()
{
	return config_;
}

bool Sensor::init(SensorConfig config)
{
	config_ = config;

	return true;
}