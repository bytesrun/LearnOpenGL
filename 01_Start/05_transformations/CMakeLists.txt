aux_source_directory(. SRC)
add_library(transformations  ${SRC})
target_include_directories(transformations 
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                            PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glad/include
							PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glfw-3.3.2/include
                            PRIVATE ${PROJECT_SOURCE_DIR}/ShaderClass
                            PRIVATE ${PROJECT_SOURCE_DIR}/LoadImg
                            #PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glm
                            )

target_link_libraries(transformations PUBLIC glfw glad shader stbimg)