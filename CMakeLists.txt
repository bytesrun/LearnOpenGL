cmake_minimum_required(VERSION 3.15)
project(LearnOpenGL)
#add_definitions(-std=c++11)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
if(OpenGL_FOUND)
	message(STATUS "OpenGL Found")
else(OpenGL_FOUND)
	 message(FATAL_ERROR ”OpenGL library not found”)
endif(OpenGL_FOUND)

add_subdirectory(Dependencies/glfw-3.3.2)
#list(APPEND EXTRA_LIBS glfw)

add_subdirectory(Dependencies/glad)
#list(APPEND EXTRA_LIBS glad)
#list(APPEND EXTRA_INCLUDE Dependencies/glad/include)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories(Dependencies
					Dependencies/glad/include
					Dependencies/glfw-3.3.2/include
					Dependencies/glm)
add_subdirectory(ShaderClass)
#list(APPEND EXTRA_LIBS shader)

add_subdirectory(LoadImg)

add_subdirectory(01_Start)
list(APPEND EXTRA_LIBS 01_Start)

add_subdirectory(02_Lighting)
list(APPEND EXTRA_LIBS 02_Lighting)

aux_source_directory(. SRC)
add_executable(LearnOpenGL ${SRC})
add_custom_command(TARGET LearnOpenGL POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:LearnOpenGL>)
#add_custom_command(TARGET LearnOpenGL PRE_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_if_different
#	"${PROJECT_SOURCE_DIR}/shader.vs"
#	$<TARGET_FILE_DIR:LearnOpenGL>)
#
#add_custom_command(TARGET LearnOpenGL PRE_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_if_different
#	"${PROJECT_SOURCE_DIR}/shader.fs"
#	$<TARGET_FILE_DIR:LearnOpenGL>)

#target_link_libraries(LearnOpenGL PUBLIC ${EXTRA_LIBS} OpenGL::GL)
target_link_libraries(LearnOpenGL PUBLIC ${EXTRA_LIBS})
