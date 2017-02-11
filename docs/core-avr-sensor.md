####Overview

The `avr-core-sensor` library focuses on managing, initializing, and polling sensors. There is a hard dependency on the [core-avr-data](core-avr-data.md) library.

![Overview](https://www.lucidchart.com/publicSegments/view/d404875d-51d6-4e6a-911f-892a003210e5/image.png)

####SensorManager

The entry point for managing sensors is `SensorManager`. New `Sensor` instances are added to the manager with a corresponding `SensorConfig`. The config holds information that informs the `SensorManager` how to use the `Sensor`.

`SensorManager::update()` is called on an update loop. The manager then moves through the list of `Sensor`s it maintains and polls them according to the configuration. Collected data is saved to a persistent store by the `FileManager`.


####Data

Sensor data is informed by the backend storage mechanism which you can read more about in the [core-avr-data: Storage](core-avr-data.storage.md) document.

![Data Layout.](https://www.lucidchart.com/publicSegments/view/77f88ead-2daa-4ba4-a37f-085c02dca509/image.png)

Because sensors are polled at a steady interval, given the start time, we can extrapolate timestamps for each collected value. This is notably different than how `Whisper` stores data on the backend. When this data is passed to the backend, it will pull out timestamps as well. To allow for disruptions to data, we also separate `Point`s into `PointList` collections. This allows devices to be disconnected for a time, without ruining all the data.

> **Note**: The `Point` instances within `PointList` may get too far apart. This is okay within some specified epsilon, probably even minutes.