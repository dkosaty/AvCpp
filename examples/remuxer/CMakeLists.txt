add_executable(remuxer main.cpp)

target_include_directories(remuxer PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(remuxer PRIVATE avcpp)