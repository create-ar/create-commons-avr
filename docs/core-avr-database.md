[TOC]

####Overview

`avr-core-database` is our library for easily reading and writing databases.

![High level overview.](https://www.lucidchart.com/publicSegments/view/8fd76fcb-2ed5-469e-9c44-70b3132bcc5e/image.png)

###### Database

A `Database` is a fixed size store for _timestamped floating point values_. A set of values can be added to the database, and it will automatically affix a timestamp and pass  this full record to the stream.

Similar to `DatabaseManager`, a `Database` has both an `init` and a `load` method, useful in the same capacities. These methods should not be called directly. Instead, use the `DatabaseManager` API to create and retreive databases.

To add values to the store, call `Database::add`.

Many records may be retrieved at once using `Database::dump`.

`Database::flush()` can be called when you need to ensure data has been written to the stream.

###### Record Format

Data format is informed by backend considerations that can be read about **[here](core-avr-database.storage.md)**. For each specific group of values, we store them on the stream in a record data structure. The specific format is:

`[unsigned long][float]...[float]`

For a specific `Database`, we must always store the same number of floating point values per record. The record is prefixed by a timestamp, floats are then written out.

###### DatabaseManager

The `DatabaseManager` class exposes an API for manipulating these databases, which are created and manipulated via URI. `DatabaseManager` stores a fixed size header that helps with looking up databases. When initialized, this header is read into memory.

`DatabaseManager::init` writes a new `DatabaseManagerHeader` to the stream. This effectively wipes all databases.

`DatabaseManager::load` loads an existing header from a stream. This is useful most of the time, i.e., when there are databases in the stream that you wish to manipulate.

>**Note:** Either `init` or `load` must be called prior to using the other parts of the `DatabaseManager` API.

When a `Database` is **created** with `DatabaseManager::create`, the manager wipes a portion of the `AvrStream` equal to the full file size, then writes a static sized `DatabaseHeader`. A new, unmanaged `Database` object is returned, which can be used to manipulate the data. 

>**Note:** `Database` objects returned from this API are _not_ managed by the `DatabaseManager` and should be freed with `delete`.

When a `Database` is **retrieved** via `DatabaseManager::get`, a new `Database` object is returned and created, pointing to the necessary piece of data. The data is not loaded into memory, only the header. This allows you to have many databases open without significant memory overhead.

>**Note:** `Database` objects returned from this API are _not_ managed by the `DatabaseManager` and should be freed with `delete`.

#### Further Reading

* **[core-avr-io](core-avr-io.md)** describes the `AvrStream` abstraction, which allows a `Database` to swap persistence layers. Eg: in-memory, EEPROM, SD card, etc.
* **[core-avr-storage](core-avr-database.storage.md)** describes full stack storage mechanisms and formats.
* **[SPI](https://www.arduino.cc/en/reference/SPI)**
* **[SPIEEPROM](https://www.arduino.cc/en/Tutorial/SPIEEPROM)**