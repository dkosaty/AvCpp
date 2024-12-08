cmake_minimum_required(VERSION 3.22.1)

project(avcpp)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SOURCES)
file(GLOB HEADERS *.h)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} avutil avformat avcodec)
