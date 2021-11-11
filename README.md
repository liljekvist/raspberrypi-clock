# A clock and event schedule
This project is based on raylib to render a simple 2D ui to have up on a screen or tv. The applications main purpose is to make it easier for TE4 (NTI) to keep track of time. 

## Short build info
First you need to build raylib and associated librarys. You can do that with `make setup`. Raylib is a static indlude.

To build and run the makefile, run `make` in main directory (where the makefile is located). This will remove the built program after running.

To build and save the compiled program, run `make bin/app`.

## Current supported operating systems
GNU/Linux and MacOS is supported. Tested on `Arch 2021.11.01` and `macOS 11.6 20G165 x86_64`.

## Third party dependencies 
### Raylib deps
* GNU/Linux - https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
* MacOS - https://github.com/raysan5/raylib/wiki/Working-on-macOS
* raylibcpp wrapper - https://github.com/RobLoach/raylib-cpp

### Project local deps
* Curl, Used by libcurl
* libjsoncpp

## License
This project is licenced under an unmodified zlib/libpng licence, which is an OSI-certified, BSD-like licence that allows static linking with closed source software. Check docs/LICENCE for further details.
