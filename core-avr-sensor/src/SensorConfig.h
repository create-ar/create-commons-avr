#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

/**
 * @brief      Configuration for sensors.
 */
struct SensorConfig
{
	/**
	 * Number of milliseconds we should wait between polls.
	 */
	int pollIntervalMs;
};

#endif