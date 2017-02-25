#include <catch.hpp>

#include <DatabaseManager.h>
#include <MemoryStream.h>

#include "SensorManager.h"
#include "Sensor.h"
#include "SensorConfig.h"

class DummySensor : public Sensor
{
public:
	int pollCount;

	~DummySensor()
	{
		//
	}

	float poll() override
	{
		pollCount += 1;

		return 0;
	}
};

TEST_CASE("SensorManager", "[SensorManager]")
{
	// setup
	MemoryStream* stream = new MemoryStream(4096);
	DatabaseManager* data = new DatabaseManager(stream);
	
	DatabaseManagerConfig config;
	data->init(config);

	SensorManager* sensors = new SensorManager(data);

	{
		DummySensor* dummy = new DummySensor();
		SensorConfig sensorConfig;
		sensorConfig.pollIntervalMs = 10;

		dummy->init(sensorConfig);

		REQUIRE(sensors->add(dummy));

		sensors->update(1);

		REQUIRE(dummy->pollCount == 0);

		sensors->update(9);

		REQUIRE(dummy->pollCount == 1);

		sensors->update(100);

		REQUIRE(dummy->pollCount == 2);

		REQUIRE(sensors->remove(dummy));

		sensors->update(100);

		REQUIRE(dummy->pollCount == 2);

		delete dummy;
	}

	// teardown
	delete sensors;
	delete data;
	delete stream;
}