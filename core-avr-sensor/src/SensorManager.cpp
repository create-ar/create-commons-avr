#include "SensorManager.h"

SensorManager::SensorManager(DatabaseManager* data)
	: _data(data)
{
	//
}

SensorManager::~SensorManager()
{
	//
}

bool SensorManager::add(Sensor* sensor)
{
	if (_sensors.Contains(sensor))
	{
		return false;
	}

	_sensors->add(sensor);

	return true;
}

bool SensorManager::remove(Sensor* sensor)
{
	return _sensors->remove(sensor);
}

void update(double dt)
{
	
}