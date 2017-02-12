#### Overview

The `core-avr-logging` library provides a very basic set of logging utilities modeled after familiar logging frameworks.

##### Log

`Log` provides a static interface for logging. Generally, `Log` is not used directly, but instead configured with log targets and formatters.

##### Logger

Usually, you will create an instance of `Logger`, which will allow for logging at different levels with basic category handling. A class can declare a `Logger` instance, and pass all logs through this object, which forwards it along to the static interface on `Log`.

##### LogTarget

When working with Arduinos, the `Serial` interface is one of the many interface you may want to use to pass logs. Once hardware becomes more advanced, `SoftwareSerial` or even `core-avr-messaging` may become better options. This is what `LogTarget` allows for: changing where logs go, even at runtime.

Simply set target using `Log`'s static interface.

##### LogFormatter

Finally, make your logs look how you want them too by implementing a `LogFormatter`. A basic implementation is provided in `DefaultLogFormatter`.