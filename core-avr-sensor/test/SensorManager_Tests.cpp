#include <catch.hpp>

#include <DatabaseManager.h>
#include <MemoryStream.h>

#include "SensorManager.h"
#include "Sensor.h"
#include "SensorConfig.h"

class DummySensor : public Sensor
{
public:
	float poll() override
	{
		return 0f;
	}
};

TEST_CASE("SensorManager", "[SensorManager]")
{
	// setup
	MemoryStream* stream = new MemoryStream(4096);
	DatabaseManager* data = new DatabaseManager(stream);
	
	DatabaseConfig config;
	data->init(config);

	SensorManager* sensors = new SensorManager(data);

	

	// teardown
	delete sensors;
	delete data;
	delete stream;
}