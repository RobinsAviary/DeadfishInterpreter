# Robinfish Interpreter
This is a [Deadfish](https://esolangs.org/wiki/Deadfish) [Interpreter](https://www.geeksforgeeks.org/introduction-to-interpreters/) written in [C++20](https://en.cppreference.com/w/cpp/20). (Overkill? Probably.) It contains various other operators from a smattering of Deadfish extensions, thus the different name.

It supports ``.df`` and ``.txt`` files being dragged into it/specified as well as a terminal mode when the application is directly opened.

## Operators

| Operator | Explantation                                                                          |
| -------- | ------------------------------------------------------------------------------------- |
| i        | Increment the accumulator.                                                            |
| d        | Decrement the accumulator.                                                            |
| s        | Square the accumulator.                                                               |
| o        | Output the accumulator (As a number).                                                 |
| h        | Halt the program.                                                                     |
| r        | Square root the accumulator                                                           |
| c        | Output the accumulator as an ASCII character. _**NOTE:**_ Numbers outside 0-255 do nothing. |
| w        | Print "Hello, World!"                                                                 |
| ;        | Reset the accumulator to zero.                                                        |

## Command Line Parameters
All command line parameters begin with ``-``

I may add these back, we'll see.

## Building
This interpreter exists entirely within a source code file and a single library, so building should be trivial with any program.

## License
This interpreter, library, and its source code are provided under the [MIT License](https://en.wikipedia.org/wiki/MIT_License). The original language and the superset are in the Public Domain.
