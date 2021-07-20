aux_source_directory(. SRC)
add_library(helloWindow ${SRC})
target_include_directories(helloWindow
							INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
							PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glad/include
							PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.2/include)
							
target_link_libraries(helloWindow PUBLIC glfw glad OpenGL::GL)