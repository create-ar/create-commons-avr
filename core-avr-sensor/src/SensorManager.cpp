#include "SensorManager.h"

#include <Log.h>
#include <Iterator.h>

namespace
{
	#define SENSOR_MAX_VALUES 8

	float _readBuffer[SENSOR_MAX_VALUES];
}

SensorManager::SensorManager(DatabaseManager* data)
	: _data(data)
{
	_logger = Log::logger("SensorManager");
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

	// create a new record
	SensorRecord* record = new SensorRecord();
	record->sensor = sensor;

	// construct uri
	char uri[SENSOR_ID_LEN + 8];
	SensorConfig config = sensor->config();
	sprintf(uri, "SENSOR__%s", config.identifier);

	// retrieve database
	{
		Database* database = _data->get(uri);
		if (nullptr == database)
		{
			_logger->info("Creating database.");

			if (!_data->create(uri, config.dbSize, config.numValues))
			{
				_logger->error("Could not create database.");
				return false;
			}

			database = _data->get(uri);
			if (nullptr == database)
			{
				_logger->error("Database created but could not be retrieved.");
				return false;
			}
		}
		record->database = database;
	}

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

		SensorConfig config = sensor->config();
		int pollInterval = config.pollIntervalMs;
		if (record->accumulator >= pollInterval)
		{
			if (sensor->poll(_readBuffer))
			{
				// 
			}

			record->accumulator -= pollInterval;
		}
	}

	delete it;
}