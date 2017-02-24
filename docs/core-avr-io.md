#### Overview

The `core-avr-io` library provides various objects and abstractions that are useful for IO on AVR.

##### AvrStream

`AvrStream` is the interface for reading and writing bytes. The naming convention is to avoid naming collisions with various standard library streams.

##### MemoryStream

When the need arises to manipulate a fixed size memory buffer, `MemoryStream` provides a reliable implementation. We provide thorough testing in the `test/` directory.

##### EEPROMStream

The EEPROMStream is one of the more complicated implementations. It covers up the morass of dealing with EEPROM through the `DataFlash` library. Paging is taken care of behind the scenes.