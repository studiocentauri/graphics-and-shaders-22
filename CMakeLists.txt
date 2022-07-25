# Setup CMake version
cmake_minimum_required(VERSION "3.16.3")

# Setup project target
project(graphics-and-shaders)

# Set C/C++ compiler
set(CMAKE_C_STANDARD 99 CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "")

# Set Project Flags
set(BUILD_SHADER_VIEWER 0 CACHE INTERNAL "")

# Set folder paths
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(THIRD_PARTY_SRCS "${PROJECT_DIR}/includes/thirdparty")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_DIR}/cmake/modules")

# GLFW Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGL")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${THIRD_PARTY_SRCS}/glfw/ "${CMAKE_CURRENT_BINARY_DIR}/glfw")
add_subdirectory(${THIRD_PARTY_SRCS}/glad/ "${CMAKE_CURRENT_BINARY_DIR}/glad")

# Assimp flags
set(ASSIMP_INSTALL OFF CACHE BOOL "disable assimp install")
add_subdirectory(${THIRD_PARTY_SRCS}/assimp/ "${CMAKE_CURRENT_BINARY_DIR}/assimp")

# Include paths
include_directories(${PROJECT_DIR}/includes)
include_directories(${THIRD_PARTY_SRCS}/glad/include)
include_directories(${THIRD_PARTY_SRCS}/glfw/include)
include_directories(${THIRD_PARTY_SRCS}/stb_image)
include_directories(${THIRD_PARTY_SRCS}/imgui)
include_directories(${THIRD_PARTY_SRCS}/glm/)
set(ASSIMP_INCLUDE_DIRS "${THIRD_PARTY_SRCS}/assimp/include" "${CMAKE_CURRENT_BINARY_DIR}/assimp/include")
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${PROJECT_DIR}/configuration)
configure_file(${PROJECT_DIR}/configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

# Define files
file(GLOB_RECURSE FILES_IMGUI "${THIRD_PARTY_SRCS}/imgui/*.cpp")
file(GLOB_RECURSE FILES_UTILS "${PROJECT_DIR}/src/utility/*.cpp")
file(GLOB_RECURSE FILES_GRAPHICS "${PROJECT_DIR}/src/rendering/*.cpp" "${THIRD_PARTY_SRCS}/glad/src/*.c" "${THIRD_PARTY_SRCS}/stb_image/*.cpp")
file(GLOB_RECURSE FILES_OBJECT "${PROJECT_DIR}/src/object/*.cpp")
file(GLOB_RECURSE FILES_GUI "${PROJECT_DIR}/src/gui/*.cpp")

# Add common renderer library
add_library(
        graphics-renderer
        ${FILES_GRAPHICS}
        ${FILES_UTILS}
        ${FILES_OBJECT}
        ${FILES_GUI}
        ${FILES_IMGUI})

# Add required executable
add_executable(
            ${PROJECT_NAME}
            src/Main.cpp)
target_link_libraries(
                    ${PROJECT_NAME}
                    graphics-renderer 
                    ${CMAKE_DL_LIBS}  
                    glad
                    glfw 
                    ${GLFW_LIBRARIES} 
                    assimp)
if(${BUILD_SHADER_VIEWER})
add_executable(
                shader-viewer
                src/ShaderViewer.cpp)
target_link_libraries(
                    shader-viewer
                    graphics-renderer 
                    ${CMAKE_DL_LIBS}  
                    glad
                    glfw 
                    ${GLFW_LIBRARIES} 
                    assimp)
endif()
