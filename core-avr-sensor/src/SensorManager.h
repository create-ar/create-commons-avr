#ifndef SENSORMANAGER_H
#define SENSORMANAGER_H

#include <DatabaseManager.h>
#include <LinkedList.h>

#include "Sensor.h"

struct SensorRecord
{
	Sensor* sensor;
	double lastUpdate;
}

class SensorManager
{
private:
	DatabaseManager* _data;
	LinkedList<SensorRecord> _sensors;

public:
	SensorManager(DatabaseManager* data);
	~SensorManager();

	bool add(SensorRecord* sensor);
	bool remove(SensorRecord* sensor);
	void update(double dt);
};

#endif