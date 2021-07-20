aux_source_directory(. SRC)
add_library(CSetVao ${SRC})
target_include_directories(CSetVao
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                            PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glad/include
                            #PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glm
                            ) 
target_link_libraries(CSetVao PUBLIC glad)