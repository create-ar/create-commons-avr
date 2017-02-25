#ifndef SENSORCONFIG_H
#define SENSORCONFIG_H

#include <stdlib.h>
#include <Database.h>

// Length of id field.
#define SENSOR_ID_LEN 8

// One week of data, polled every 10 secs.
// Assuming AT45DB321E chip, ~ 4MB this means ~8 sensors.
#define SENSOR_DB_SIZE 483840

/**
 * @brief      Configuration for sensors.
 */
class SensorConfig
{
public:
	/**
	 * Unique identifier for this sensor. This should remain the same across
	 * sessions.
	 */
	char identifier[SENSOR_ID_LEN];

	/**
	 * Number of milliseconds we should wait between polls.
	 */
	int pollIntervalMs;

	/**
	 * Size of database in bytes.
	 */
	int dbSize;

	/**
	 * @brief      Constructor. Requires a unique identifier for this sensor.
	 * Should be constant across sessions.
	 *
	 * @param[in]  id    The unique identifier.
	 * @param[in]  databaseSize   Size of the database in bytes.
	 */
	SensorConfig(
		const char ident[SENSOR_ID_LEN],
		int databaseSize)
		: dbSize(databaseSize)
	{
		memcpy(identifier, ident, SENSOR_ID_LEN);
	}

	/**
	 * @brief      Destructor.
	 */
	virtual ~SensorConfig()
	{
		//
	}
};

#endif