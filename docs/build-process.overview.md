#### Overview

The `core-avr` libraries are built into both static libraries and executables for testing. We use `make` for compilation and linking. `gradle` is also configured (but not required) for dependency resolution, code + project generation, and documentation.

`make` is configured to build to two cpu architectures: `x86` and `avr`. The former for local unit tests, the latter for Arduino projects.

##### Dependencies

* make
* gradle	(optional)
* doxygen	(optional)

##### Configuration

All `make` configuration is contained in [**`properties.mk`**](https://github.com/Open-farm/openfarm-core-avr/blob/master/properties.mk). Each subproject includes this file to configure both builds. This file is heavily documented with the specifics you'll need to adjust for your environment.

##### Building for Arduino

When writing an Arduino application, you can either directly include the source files, or link against static libraries. `avr-g++` requires detailed hardware knowledge to compile correctly (Arduino variant, cpu clock, cpu name), so you will need to configure the properties file if you wish to use static libraries.

##### Building for x86 + Testing

During development, we build x86 static libraries to the `/lib` folder. We use [`catch`](https://github.com/philsquared/Catch) to write tests. This is why we make x86 object files-- so we can link these into a testable executable.

>**Note:** This process currently requires a *nix shell for specific commands. For building on Windows, please see [this guide](build-process.windows.md) for specific considerations.

##### Gradle

We also include a number of `gradle` tasks.

* **build** - Builds static libraries and test executables
* **gendocs** - Generates documentation using `doxygen`. This is output in [`docs/generated`](../generated/index.html).
* **genapi** - Generates a project archetype. Requires `-Papi` property, eg - `gradle genapi -Papi=core-avr-ds`.
* **test** - Runs all unit test executables.


##### Gradle Properties

You may also pass properties to `gradle` using the `-P[PROPERTY]` form.

* **verbose** - Adds additional logging.