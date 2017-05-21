#include "sensor_manager.h"

#include <log.h>
#include <iterator.h>

namespace
{
	#define kSensorMaxValues 8

	float readBuffer_[kSensorMaxValues];
}

SensorManager::SensorManager(DatabaseManager* data)
	: data_(data)
{
	logger_ = Log::logger("SensorManager");
}

SensorManager::~SensorManager()
{
	// delete records
	Iterator<SensorRecord>* it = sensors_.it();
	while (it->moveNext())
	{
		delete it->current();
	}
	
	delete it;
}

bool SensorManager::add(Sensor* sensor)
{
	// don't add it twice
	Iterator<SensorRecord>* it = sensors_.it();
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
	char uri[kSensorIdLen + 8];
	SensorConfig config = sensor->config();
	sprintf(uri, "SENSOR__%s", config.identifier);

	// retrieve database
	{
		Database* database = data_->get(uri);
		if (nullptr == database)
		{
			logger_->info("Creating database.");

			if (!data_->create(uri, config.dbSize, config.numValues))
			{
				logger_->error("Could not create database.");
				return false;
			}

			database = data_->get(uri);
			if (nullptr == database)
			{
				logger_->error("Database created but could not be retrieved.");
				return false;
			}
		}
		record->database = database;
	}

	sensors_.add(record);

	return true;
}

bool SensorManager::remove(Sensor* sensor)
{
	bool removed = false;

	Iterator<SensorRecord>* it = sensors_.it();
	while (it->moveNext())
	{
		SensorRecord* record = it->current();
		if (record->sensor == sensor)
		{
			sensors_.remove(record);
			
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
	Iterator<SensorRecord>* it = sensors_.it();
	while (it->moveNext())
	{
		SensorRecord* record = it->current();
		Sensor* sensor = record->sensor;
		record->accumulator += dt;

		SensorConfig config = sensor->config();
		int pollInterval = config.pollIntervalMs;
		if (record->accumulator >= pollInterval)
		{
			if (sensor->poll(readBuffer_))
			{
				// 
			}

			record->accumulator -= pollInterval;
		}
	}

	delete it;
}