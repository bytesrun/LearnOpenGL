aux_source_directory(. SRC)
add_library(02_BasicLighting ${SRC})
target_include_directories(02_BasicLighting
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})