####Overview

`avr-core-data` is our library for easily reading and writing from non-volatile memory. There are some limitations of working with EEPROM that this library attempts to smooth out.

![High level overview.](https://www.lucidchart.com/publicSegments/view/8e433611-4d2d-43cd-813b-36c5136e3d7b/image.png)

##### EEPROMStream

Working with EEPROM on an Arduino involves complicated SPI signaling logic as well as dealing with paging. This class abstracts that away to a nicer interface that exposes data as a continuous block of data.

##### FileManager

The `FileManager` class exposes a _fixed-size_ file manipulation API, based on URI. `FileManager` tracks files using a header that maps URI to offset. When initialized, this header is read into memory. When a file is created or requested, the URI is mapped through the header to an offset in EEPROM. A `File` object is returned, which can be used to manipulate the data. `File::flush()` is called when the data should be written to EEPROM. `File::refresh()` is called when the data should be read from EEPROM again.

#####Further Reading

* **[SPI](https://www.arduino.cc/en/reference/SPI)**
* **[SPIEEPROM](https://www.arduino.cc/en/Tutorial/SPIEEPROM)**