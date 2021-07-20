aux_source_directory(. SRC)

add_library(01_Colors ${SRC})

target_include_directories(01_Colors 
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})