#### Overview

We collect sensor data with varying granularities. At the bottom layer, the device aggregates data and stores as much as possible via [core-avr-database](core-avr-database.md). The phone also has an aggregation and storage mechanism before it hits the backend, which has a third aggregation system.

It's helpful to define the end points first, then dive into the middle.

##### Device Data Collection and Aggregation

The device will collect data from sensors through the [core-avr-sensor](core-avr-sensor.md) library. This data is polled at regular intervals from various sensors. Different sensors will have different poll intervals and data storage needs.

Once a device has successfully synced with a mobile, all data is cleared. Syncing may be forced by a user, however it is also automatically synced on an interval. To keep as much data as possible, data is eventually aggregated.

Data is aggregated as a function of how old the data is, storage requirements of sensors, and how much memory is left on the device: f(age, required, memory). As that function hits a certain point, we start to store information about the data, rather than the data itself: eg - min, max, average over an interval. Further on along that function, we will start dropping the oldest data.

There is a common component that can _simulate_ that function, so that the mobile and backend can make reasonable judgements about what is happening to data on the device. For instance, so we can send a notification to the user when we know that data is being lost.

This data is then stored on device through the [core-avr-database](core-avr-database.md) library.

##### Mobile Syncing

Once a connection is established from device to mobile, the device can automatically or forcibly sync data with the mobile. On successful sync, all data is wiped from the mobile.

Once a mobile has the device data, that data is pushed through an aggregation process similar to the device. Data is bundled and sent in blobs to the backend API for storage.

##### Backend API

The backend API can perform operations on time-series formatted data. It uses [Whisper](https://github.com/graphite-project/whisper) to store this data. Further reading [here](http://graphite.readthedocs.io/en/latest/whisper.html).

>"Whisper allows for higher resolution (seconds per point) of recent data to degrade into lower resolutions for long-term retention of historical data."

This backend works in much the same way as [Carbon](https://github.com/graphite-project/carbon). There is a `relay` that accepts requests, an `aggregator` that tames data into aggregations, and a `cache` that is used for retrieval. The main difference is that in our structure, `Graphite-Web` is essentially an HTTP api for data retrieval, embedded in our backend.

![Carbon diagram.](https://raw.githubusercontent.com/graphite-project/graphite-web/master/webapp/content/img/overview.png)

##### Data Format

Eventually, the data is stored via whisper as a list of timestamped points arranged in separate archives:

[`!Ld`](https://docs.python.org/3/library/struct.html#format-strings)

Since the archives are a fixed-size, we store data in archives of fixed duration. This has yet to be determined yet, but we should determine an optimal `N` milliseconds that an archive should store. Most likely this will also be based on the type of data needing stored.

Taking the data format on the backend as a model, we should also store data on device and on mobile in the same way.
