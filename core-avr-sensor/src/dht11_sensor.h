#ifndef DHT11SENSOR_H
#define DHT11SENSOR_H

#include "Sensor.h"

#include <Logger.h>
#include <Dht11.h>

#define kDht11PinName "dht11_pin"
#define kDht11NumValues 3

/**
 * @brief      Sensor implementation for the DHT11 temperature/humidity sensor.
 */
class Dht11Sensor : public Sensor
{
private:
	/**
	 * Logger for this class.
	 */
	Logger* logger_;

	/**
	 * Sensor instance.
	 */
	Dht11* dht11_;

	/**
	 * @brief      Retrieves dewpoint.
	 * reference (1) : http://wahiduddin.net/calc/density_algorithms.htm
	 * reference (2) : http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
	 *
	 * @param[in]  celsius   Temperature in celcius.
	 * @param[in]  humidity  Humidity.
	 *
	 * @return     Dewpoint calculation.
	 */
	float dewPoint(double celsius, double humidity);

public:
	/**
	 * @brief      Constructor.
	 */
	Dht11Sensor();

	/**
	 * @brief      Destructor.
	 */
	~Dht11Sensor()
	{
		if (nullptr != dht11_)
		{
			delete dht11_;
		}
	}

	/**
	 * @brief      Initializes the sensor with its configuration. This sensor
	 * must have a pin, kDht11PinName, and can gather between 1 and 3 values,
	 * inclusive.
	 *
	 * @param[in]  config  The configuration for this sensor.
	 *
	 * @return     True if successful.
	 */
	bool init(SensorConfig config) override;

	/**
	 * @brief      Polls the sensor for values.
	 *
	 * @param[in]  values  Values buffer to write to.
	 *
	 * @return     True if successful.
	 */
	bool poll(const float* values) override;
};

#endif