#### Overview

The `core-avr` libraries are built into static libraries using `gradle` to manage dependencies and `make` to build and link.

##### Dependencies

* gradle
* make
* doxygen

##### Build

To build all projects, run `gradle build`.

>**This process requires a *nix shell for specific commands. For building on Windows, please see [this guide](build-process.windows.md) for specific considerations.**

##### Tasks

You may also run tasks individually.

* **buildavr** - Builds static libraries for avr architecture.
* **buildtests** - Builds test executables for _current_ architecture.
* **gendocs** - Generates documentation using `Doxygen`. This is output in [`docs/generated`](../generates/index.html).
* **gentest** - Generates unit test archetype for a project. Requires `-Papi` property, eg - `gradle gentest -Papi=core-avr-ds`.


##### Properties

You may also pass properties to `gradle` using the `-P[PROPERTY]` form.

* **verbose** - Adds additional logging.