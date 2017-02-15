#### Overview

The `core-avr-logging` library provides a very basic set of logging utilities modeled after familiar logging frameworks.

![Overview.](https://www.lucidchart.com/publicSegments/view/5b7ca2d9-799d-4b97-807d-7e9cce16e56f/image.png)

#### Usage

Setup:
```
auto formatter = new DefaultFormatter();
auto target = new SerialTarget();

Log::addTarget(target);
Log::setFormatter(formatter);
```

Log:
```
auto logger = Log::logger("MyClass");
...
logger->debug("This is a test!");
```

##### Log

`Log` provides a static interface for logging. Generally, `Log` is not used directly, but instead configured with log targets and formatters.

##### Logger

Usually, you will create an instance of `Logger`, which will allow for logging at different levels with basic category handling. A class can declare a `Logger` instance, and pass all logs through this object, which forwards it along to the static interface on `Log`.

##### LogTarget

When working with Arduinos, the `Serial` interface is one of the many interface you may want to use to pass logs. Once hardware becomes more advanced, `SoftwareSerial` or even `core-avr-messaging` may become better options. This is what `LogTarget` allows for: changing where logs go, even at runtime.

Simply set target using `Log`'s static interface.

##### LogFormatter

Finally, make your logs look how you want them too by implementing a `LogFormatter`. A basic implementation is provided in `DefaultFormatter`. This class will output files in this format:

`[{Level}][{Category}] {Message}`

Eg.-

`[debug][FileManager] This is a log!`