aux_source_directory(. SRC)
#include_directories(../Dependencies/glm)
add_library(shader ${SRC})
target_include_directories(shader
                            INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                            PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glad/include
                            #PRIVATE ${PROJECT_SOURCE_DIR}/Dependencies/glm
                            ) 
target_link_libraries(shader PUBLIC glad)