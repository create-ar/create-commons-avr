#ifndef SENSOR_H
#define SENSOR_H

#include "SensorConfig.h"

/**
 * @brief      Abstract base class for a Sensor.
 */
class Sensor
{
private:
	/**
	 * Configuration for this sensor.
	 */
	SensorConfig _config;

public:
	/**
	 * @brief      Constructor.
	 */
	Sensor()
		: _config("DEFAULT", SENSOR_DB_SIZE)
	{
		
	}

	/**
	 * @brief      Destructor.
	 */
	virtual ~Sensor()
	{
		//
	}

	/**
	 * @brief      Retrieves the configuration for this sensor.
	 *
	 * @return     Config for this object.
	 */
	virtual SensorConfig config();

	/**
	 * @brief      Initializes the sensor.
	 *
	 * @param[in]  config  The configuration for this sensor.
	 *
	 * @return     True if sensor initialization was successful.
	 */
	virtual bool init(SensorConfig config);

	/**
	 * @brief      Polls the sensor for a value.
	 *
	 * @return     A float value.
	 */
	virtual float poll() = 0;
};

#endif