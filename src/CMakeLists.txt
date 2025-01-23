aux_source_directory(. SOURCES)
file(GLOB HEADERS *.h)

add_library(avcpp ${HEADERS} ${SOURCES})

target_link_libraries(avcpp PUBLIC avutil avformat avcodec)