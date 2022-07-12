cmake_minimum_required(VERSION "3.16.3")

project(graphics-and-shaders)

set(CMAKE_CXX_STANDARD 17)

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}/std:c++17")
endif(MSVC)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules")

find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(ASSIMP REQUIRED)

if(ASSIMP_FOUND)
  include_directories(${ASSIMP_INCLUDE_DIR})
endif(ASSIMP_FOUND)

include_directories(includes)
include_directories(includes/thirdparty)
include_directories(configuration)
configure_file(configuration/root_directory.h.in configuration/root_directory.h)
include_directories(${CMAKE_BINARY_DIR}/configuration)

if(WIN32)
  link_directories(lib)
endif()

add_executable(
  graphics-and-shaders

  src/Main.cpp
  # src/ShaderToy.cpp
  src/thirdparty/glad.c
  src/thirdparty/stb_image.cpp
  src/rendering/Camera.cpp
  src/rendering/Renderer.cpp
  src/rendering/Shader.cpp
  src/rendering/Texture.cpp
  src/utility/FileSystem.cpp
  src/object/Transform.cpp
  src/object/Actor.cpp
  src/object/Mesh.cpp
  src/object/Model.cpp
  src/gui/GUI.cpp
  src/gui/Widgets.cpp
  includes/thirdparty/imgui/imgui.cpp
  includes/thirdparty/imgui/imgui_draw.cpp
  includes/thirdparty/imgui/imgui_demo.cpp
  includes/thirdparty/imgui/imgui_widgets.cpp
  includes/thirdparty/imgui/imgui_tables.cpp
  includes/thirdparty/imgui/imgui_impl_glfw.cpp
  includes/thirdparty/imgui/imgui_impl_opengl3.cpp
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

  target_link_libraries(graphics-and-shaders assimp)

if(WIN32)
  add_custom_command(TARGET graphics-and-shaders POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_SOURCE_DIR}/dll/assimp-vc142-mtd.dll"
  $<TARGET_FILE_DIR:graphics-and-shaders>
  )
endif(WIN32)