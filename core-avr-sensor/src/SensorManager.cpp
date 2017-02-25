#include "SensorManager.h"

#include <Iterator.h>

SensorManager::SensorManager(DatabaseManager* data)
	: _data(data)
{
	//
}

SensorManager::~SensorManager()
{
	// delete records
	Iterator<SensorRecord>* it = _sensors.it();
	while (it->moveNext())
	{
		delete it->current();
	}

	delete it;
}

bool SensorManager::add(Sensor* sensor)
{
	// don't add it twice
	Iterator<SensorRecord>* it = _sensors.it();
	while (it->moveNext())
	{
		SensorRecord* record = it->current();
		if (record->sensor == sensor)
		{
			return false;
		}
	}

	SensorRecord* record = new SensorRecord();
	record->sensor = sensor;

	_sensors.add(record);

	return true;
}

bool SensorManager::remove(Sensor* sensor)
{
	bool removed = false;

	Iterator<SensorRecord>* it = _sensors.it();
	while (it->moveNext())
	{
		SensorRecord* record = it->current();
		if (record->sensor == sensor)
		{
			_sensors.remove(record);
			
			delete record;

			removed = true;
			break;
		}
	}

	delete it;

	return removed;
}

void SensorManager::update(double dt)
{
	Iterator<SensorRecord>* it = _sensors.it();
	while (it->moveNext())
	{
		SensorRecord* record = it->current();
		Sensor* sensor = record->sensor;
		record->accumulator += dt;

		int pollInterval = sensor->config().pollIntervalMs;
		if (record->accumulator >= pollInterval)
		{
			sensor->poll();

			record->accumulator -= pollInterval;
		}
	}

	delete it;
}