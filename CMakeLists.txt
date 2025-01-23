cmake_minimum_required(VERSION 3.28)

project(AvCpp)

option(BUILD_TESTING "Build tests" OFF)
option(BUILD_SHARED_LIBS "If ON is built as a shared library, otherwise as a static" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(examples)