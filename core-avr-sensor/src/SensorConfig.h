#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

/**
 * @brief      Configuration for sensors.
 */
struct SensorConfig
{
	/**
	 * URI for where the sensor data should be stored.
	 */
	char* databaseUri;

	/**
	 * Number of milliseconds we should wait between polls.
	 */
	int pollIntervalMs;
};

#endif