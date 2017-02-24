#ifndef SENSOR_H
#define SENSOR_H

class Sensor
{
public:
	Sensor()
	{
		//
	}

	~Sensor()
	{
		//
	}

	SensorConfig config() = 0;

	bool init(SensorConfig config) = 0;
	float poll() = 0;
};

#endif SENSOR_H