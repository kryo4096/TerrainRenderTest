cmake_minimum_required(VERSION 3.2)

project(game)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)
include_directories(${CMAKE_BINARY_DIR}/glfw/include)
include_directories("${PROJECT_SOURCE_DIR}/src")

SET(LIBRARIES GLEW glfw ${GLFW_LIBRARIES} ${OPENGL_LIBRARY} ${CMAKE_DL_LIBS})

file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(game ${SOURCE_FILES})
target_link_libraries(game ${LIBRARIES})
target_include_directories(game PUBLIC ${OPENGL_gl_LIBRARY})
