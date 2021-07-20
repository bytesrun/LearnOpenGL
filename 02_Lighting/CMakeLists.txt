add_subdirectory(01_Colors)
list(APPEND EXTRA_LIBS 01_Colors)

add_subdirectory(02_BasicLighting)
list(APPEND EXTRA_LIBS 02_BasicLighting)

aux_source_directory(. SRC)
add_library(02_Lighting ${SRC})

target_link_libraries(02_Lighting PUBLIC ${EXTRA_LIBS})

target_include_directories(02_Lighting 
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                            )