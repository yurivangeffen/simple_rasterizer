cmake_minimum_required(VERSION 2.8.3)
project(simple_rasterizer C CXX)


# GLFW
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
find_library(GLFW_LIBRARIES glfw3)

find_library(FOUNDATION Foundation)
find_library(OPENGL OpenGL)

SET(LIBRARIES
	${GLFW_LIBRARIES}
)

include_directories(
    include
    gl3w/include
    ${GLFW_INCLUDE_DIR}
		src
)


SET(HEADER_FILES
	src/rasterizer.h
)

add_library(gl3w
	gl3w/src/gl3w.c
	)

add_library(simple_rasterizer
	src/rasterizer.cc
	${HEADER_FILES}
)

# ------------------------------------------------------------------------------------------------
#                                               TEST
# ------------------------------------------------------------------------------------------------

add_executable(simple_rasterizer_test
    test/test.cc
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set_target_properties(simple_rasterizer PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(simple_rasterizer_test 
						simple_rasterizer
						gl3w
						${OPENGL}
						${FOUNDATION}
						${GLFW_LIBRARIES}
)