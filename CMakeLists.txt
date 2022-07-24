# Setup CMake version
cmake_minimum_required(VERSION "3.16.3")

# Setup project target
project(graphics-and-shaders)

# Set C/C++ compiler
set(CMAKE_C_STANDARD 99 CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "")

# Set Project Flags
set(BUILD_SHADERTOY 0 CACHE INTERNAL "")

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

# Find third party libs
find_package(ASSIMP REQUIRED)
if(ASSIMP_FOUND)
  include_directories(${ASSIMP_INCLUDE_DIR})
endif(ASSIMP_FOUND)

# Include paths
include_directories(${PROJECT_DIR})
include_directories(${PROJECT_DIR}/includes)
include_directories(${THIRD_PARTY_SRCS})
include_directories(${THIRD_PARTY_SRCS}/glfw/include)
include_directories(${PROJECT_DIR}/configuration)
configure_file(${PROJECT_DIR}/configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

if(WIN32)
  link_directories(lib)
endif()

# Define files
file(GLOB_RECURSE FILES_THIRD_PARTY "${PROJECT_DIR}/src/thirdparty/*.cpp" "${PROJECT_DIR}/src/thirdparty/*.c")
file(GLOB_RECURSE FILES_IMGUI "${THIRD_PARTY_SRCS}/imgui/*.cpp")
file(GLOB_RECURSE FILES_UTILS "${PROJECT_DIR}/src/utility/*.cpp")
file(GLOB_RECURSE FILES_GRAPHICS "${PROJECT_DIR}/src/rendering/*.cpp")
file(GLOB_RECURSE FILES_OBJECT "${PROJECT_DIR}/src/object/*.cpp")
file(GLOB_RECURSE FILES_GUI "${PROJECT_DIR}/src/gui/*.cpp")

# Add common renderer library
add_library(
          graphics-renderer
          ${FILES_THIRD_PARTY}
          ${FILES_GRAPHICS}
          ${FILES_UTILS}
          ${FILES_OBJECT}
          ${FILES_GUI}
          ${FILES_IMGUI})

# Add required executable
if(${BUILD_SHADERTOY})
add_executable(
            graphics-and-shaders 
            src/ShaderToy.cpp)
else()
add_executable(
            graphics-and-shaders 
            src/Main.cpp)
endif()
target_link_libraries(
                  graphics-and-shaders 
                  graphics-renderer 
                  ${CMAKE_DL_LIBS}  
                  glfw 
                  ${GLFW_LIBRARIES} 
                  assimp)

if(WIN32)
  add_custom_command(TARGET graphics-and-shaders POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/dll/assimp-vc142-mtd.dll"
  $<TARGET_FILE_DIR:graphics-and-shaders>
  )
endif(WIN32)
