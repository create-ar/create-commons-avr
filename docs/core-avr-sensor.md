[TOC]

### Overview

The `avr-core-sensor` library focuses on managing, initializing, and polling sensors. There is a hard dependency on the [core-avr-database](core-avr-database.md) library.

![Overview](https://www.lucidchart.com/publicSegments/view/de06df27-7ea7-4b5e-8841-cf43785dda7b/image.png)

###### SensorManager

The entry point for managing sensors is `SensorManager`. New `Sensor` instances are added to the manager with a corresponding `SensorConfig`. The config holds information that informs the `SensorManager` how to use the `Sensor`.

`SensorManager::update()` is called on an update loop. The manager then moves through the list of `Sensor`s it maintains and polls them according to the configuration. Collected data is saved to a persistent store by the `FileManager`.


###### Sensor Data

Sensor data is informed by the backend storage mechanism which you can read more about in the [core-avr-database: Storage](core-avr-database.storage.md) document.