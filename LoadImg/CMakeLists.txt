aux_source_directory(. SRC)
add_library(stbimg ${SRC})
target_include_directories(stbimg
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})