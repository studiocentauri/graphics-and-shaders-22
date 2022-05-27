cmake_minimum_required(VERSION "3.16.3")

project(graphics-and-shaders)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)

include_directories(includes)
include_directories(includes/thirdparty)

if(WIN32)
link_directories(lib)
endif()

add_executable(
    graphics-and-shaders
    
    src/Main.cpp
    src/thirdparty/glad.c
    src/rendering/Renderer.cpp
)

target_link_libraries(
    graphics-and-shaders ${CMAKE_DL_LIBS}
)

if(WIN32)
target_link_libraries(
        graphics-and-shaders
        ${glfw_LIBRARIES}
)
target_link_libraries(graphics-and-shaders glfw3)
else()
target_link_libraries(graphics-and-shaders glfw)
endif()
