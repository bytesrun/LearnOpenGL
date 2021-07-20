add_subdirectory(01_helloWindow)
list(APPEND EXTRA_LIBS helloWindow)

add_subdirectory(02_helloTriangle)
list(APPEND EXTRA_LIBS helloTriangle)

add_subdirectory(03_shader)
list(APPEND EXTRA_LIBS myShader)

add_subdirectory(04_texture)
list(APPEND EXTRA_LIBS texture)

add_subdirectory(05_transformations)
list(APPEND EXTRA_LIBS transformations)

add_subdirectory(06_CoordinateSystem)
list(APPEND EXTRA_LIBS CoordinateSys)

add_subdirectory(07_camera)
list(APPEND EXTRA_LIBS camera)

aux_source_directory(. SRC)
#add_library(00Start SHARED ${SRC})
add_library(01_Start  ${SRC})
target_link_libraries(01_Start PUBLIC ${EXTRA_LIBS})
target_include_directories(01_Start 
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
							
#install(TARGETS 00Start DESTINATION ${PROJECT_BINARY_DIR})