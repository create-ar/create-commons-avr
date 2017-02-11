## Build Process


##### Dependencies

* gradle
* make
* cygwin
	* Currently parts of the build process require *nix commands.
* doxygen

##### Build

To build, run `gradle build`.

>**For the time being, this process does not work in a Windows environment.**

##### Tasks

* **build** - Builds everything.
* **buildlibs** - Builds into static libraries.
* **gendocs** - Generates documentation. Automatically called by build.



##### Properties

* **verbose** - Adds additional logging.