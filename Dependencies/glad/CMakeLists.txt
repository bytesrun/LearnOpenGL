aux_source_directory(./src/ SRC)
add_library(glad ${SRC})
target_include_directories(glad
			INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include" 
			PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)