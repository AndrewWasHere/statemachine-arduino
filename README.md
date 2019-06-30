# State Machine

Base classes for implementing a finite state machine in C++ with a generic
test application and example. The library has been tested on Linux, and Arduino
(in a [separate project](https://github.com/AndrewWasHere/pongbot)).

To use the state machine library, drop the state machine source code into your
project, or grab the directory, and insert an `add_directory()` call and add
'statemachine' to the appropriate `target_link_libraries()` call in your
project's CMakeLists.txt.

The state machine library is exception-free, opting, instead, for return codes
from its interfaces. This is to allow it to compile for Arduino.

## State Machine

The state machine library consists of two files -- a C++ source file, and header
file, called `statemachine.cpp` and `statemachine.h`, respectively -- in the
`statemachine/` directory. There is also a `CMakeLists.txt` that defines how
to build the statemachine library for those using CMake.

## Tests

The state machine unit tests are in the `test/` directory. They are black box
tests of the state machine class and do not depend on any test framework.

## Dependencies

* CMake 3.10 or newer (not required for use, just for building the tests.)
* C++ Compiler of your choosing.

## License

Copyright 2019, Andrew Lin.

This library is released under the 3-Clause BSD license. See LICENSE.txt, or
https://opensource.org/licenses/BSD-3-Clause.
