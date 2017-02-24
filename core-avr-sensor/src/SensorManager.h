#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <DatabaseManager.h>
#include <LinkedList.h>

#include "Sensor.h"

/**
 * @brief      Internal struct used to track sensor updates.
 */
struct SensorRecord
{
	/**
	 * The sensor to update.
	 */
	Sensor* sensor;

	/**
	 * Accumulation of dts.
	 */
	double accumulator;
};

/**
 * @brief      Manages all sensors.
 */
class SensorManager
{
private:
	/**
	 * To store data.
	 */
	DatabaseManager* _data;

	/**
	 * List of all sensors.
	 */
	LinkedList<SensorRecord> _sensors;

public:
	/**
	 * @brief      Constructor.
	 *
	 * @param      data  The database layer.
	 */
	SensorManager(DatabaseManager* data);

	/**
	 * @brief      Destructor.
	 */
	~SensorManager();

	/**
	 * @brief      Adds a sensor.
	 *
	 * @param      sensor  The sensor to add.
	 *
	 * @return     True if the sensor was successfully added.
	 */
	bool add(Sensor* sensor);

	/**
	 * @brief      Removes a sensor.
	 *
	 * @param      sensor  The sensor to remove.
	 *
	 * @return     True if the sensor was successfully removed.
	 */
	bool remove(Sensor* sensor);

	/**
	 * @brief      Updates sensors. This will automatically determine which
	 * sensors to poll and write to the database layer.
	 *
	 * @param[in]  dt    The amount of ms that has passed since last update.
	 */
	void update(double dt);
};

#endif