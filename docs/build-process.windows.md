#### Overview

Building these projects on Windows merits special consideration. There are a handful of caveats that are addressed here.

In order to build successfully you must install `cygwin`. Running `gradle` from a Windows shell will not work properly.

##### Environment Variables

* Make sure to add `\[CYGWIN INSTALL\]/bin` to your `%PATH%` environment variable. Without this, you will be unable to run tests.