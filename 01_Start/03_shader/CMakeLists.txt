aux_source_directory(. SRC)
add_library(myShader  ${SRC})
#message(${SRC})
target_include_directories(myShader 
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                            PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glad/include
							PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.2/include
                            PRIVATE ${PROJECT_SOURCE_DIR}/ShaderClass)

target_link_libraries(myShader PUBLIC glfw glad shader)