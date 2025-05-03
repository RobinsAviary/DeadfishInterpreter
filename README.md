# Deadfish Interpreter
This is a [Deadfish](https://esolangs.org/wiki/Deadfish) [Interpreter](https://www.geeksforgeeks.org/introduction-to-interpreters/) written in [C++20](https://en.cppreference.com/w/cpp/20). (Overkill? Maybe.)

It supports ``.df`` files being dragged into it/specified as well as a terminal mode when the application is directly opened.

## Command Line Parameters
All command line parameters begin with ``-``

- ``verbose``: Verbose text output. Mostly for internal debugging.
- ``fix``: Fixes the [infamous accumulator bug](https://esolangs.org/wiki/Deadfish#Commands) in the original Deadfish implementation. Values will wrap around 0-255 as you would expect.

All parameters can be shortened to their first letter.

## Building
This interpreter exists entirely within a single source code file, so building should be trivial with any program.

## License
This interpreter is provided under the [MIT License](https://en.wikipedia.org/wiki/MIT_License).
