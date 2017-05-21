#ifndef SENSOR_H
#define SENSOR_H

#include "sensor_config.h"

/**
 * @brief      Abstract base class for a Sensor.
 */
class Sensor
{
private:
	/**
	 * Configuration for this sensor.
	 */
	SensorConfig config_;

public:
	/**
	 * @brief      Constructor.
	 */
	Sensor()
		: config_("DEFAULT", kSensorDbLen)
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
	 * @brief      Polls the sensor for values.
	 *
	 * @param      values  Output values.
	 *
	 * @return     True if the sensor could generate values.
	 */
	virtual bool poll(const float* values) = 0;
};

#endif