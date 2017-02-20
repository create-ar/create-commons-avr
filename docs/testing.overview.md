#### Overview

In order to run meaningful tests on the `core-avr` libraries, we build x86 binaries to `[project name]/build/Test.exe`. These executables each run test suites.

##### Dependencies

* [catch](https://github.com/philsquared/Catch)

##### Setup

In order to build, you'll need to download the `catch.hpp` single include and provide the path in `properties.mk`. This path will be included as a `-I` include for all projects.

##### Adding Tests

Each project has a `test` directory that new suites may be added to. If a new suite is added, simply add the new file to the `makefile` file, under the `SOURCES` property.