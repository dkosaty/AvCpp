# AvCpp

C++ wrapper of libav

## Build
1. Install package clang, cmake, ninja-build, libavformat-dev
2. mkdir build && cd build && cmake .. && cmake --build .

## Project
/src - source code of library
/examples - how to library use

## API
Remuxer is high level interface of media remuxing without transcoding process.
Demuxer and Muxer is low level interface. Demuxer read input media container and split his to streams. Muxer join streams and write his to output media container.