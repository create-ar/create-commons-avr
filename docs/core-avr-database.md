####Overview

`avr-core-database` is our library for easily reading and writing databases.

![High level overview.](https://www.lucidchart.com/publicSegments/view/8fd76fcb-2ed5-469e-9c44-70b3132bcc5e/image.png)

##### DatabaseManager

The `DatabaseManager` class exposes an API for fixed size databases, which are created and manipulated via URI. `DatabaseManager` stores a fixed size header that helps with looking up databases. When initialized, this header is read into memory.

`DatabaseManager::init` writes a new `DatabaseManagerHeader` to the stream. This effectively wipes all databases.

`DatabaseManager::load` loads an existing header from a stream. This is useful most of the time, i.e., when there are databases in the stream that you wish to manipulate.

>**Note:** Either `init` or `load` must be called prior to using the other parts of the `DatabaseManager` API.

When a `Database` is **created** with `DatabaseManager::create`, the manager wipes a portion of the `AvrStream` equal to the full file size, then writes a static sized `DatabaseHeader`. A new, unmanaged `Database` object is returned, which can be used to manipulate the data. 

>**Note:** `Database` objects returned from this API are _not_ managed by the `DatabaseManager` and should be freed with `delete`.

When a `Database` is **retrieved** via `DatabaseManager::get`, a new `Database` object is returned and created, pointing to the necessary piece of data. The data is not loaded into memory, only the header. This allows you to have many databases open without significant memory overhead.

>**Note:** `Database` objects returned from this API are _not_ managed by the `DatabaseManager` and should be freed with `delete`.

##### Database

A `Database` is a fixed size store for floating point values. Similar to `DatabaseManager`, a `Database` has both an `init` and a `load` method, useful in the same capacities. These methods should not be called directly. Instead, use the `DatabaseManager` API to create and retreive databases.

To add values to the store, call `Database::add`.

Many values may be retrieved at once using `Database::values`, which will can read a set of values into a `float[]`.

`Database::flush()` can be called when you need to ensure data has been written to the strea.

##### AvrStream

`AvrStream` is an abstraction that allows the `core-avr-database` library to read and write bytes to and from a source.

`MemoryStream` is an implementation entirely in memory. It is effectively a layer on top of a `char[]`.

`EEPROMStream` is the more useful implementation. It uses the `DataFlash` library to read and write bytes in flash memory. Working with EEPROM on an Arduino involves complicated SPI signaling logic as well as dealing with paging. This class abstracts that away to a nicer interface that exposes data as a continuous block of data.

#####Further Reading

* **[SPI](https://www.arduino.cc/en/reference/SPI)**
* **[SPIEEPROM](https://www.arduino.cc/en/Tutorial/SPIEEPROM)**