cmake_minimum_required(VERSION 2.8.3)
project(simple_rasterizer C CXX)

# GLBinding
find_package(glbinding REQUIRED)

# GLFW
find_path(GLFW_INCLUDE_DIR GLFW/glfw3.h)
find_library(GLFW_LIBRARIES glfw3)

SET(LIBRARIES
	${GLBINDING_LIBRARIES}
	${GLFW_LIBRARIES}
)

include_directories(
    include
    ${GLBINDING_INCLUDES}
    ${GLFW_INCLUDE_DIR}
)


SET(HEADER_FILES
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
						${GLBINDING_LIBRARIES}
						${GLFW_LIBRARIES}
)