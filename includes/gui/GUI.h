#ifndef GUI_H
#define GUI_H

// Third-party Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

// Standard Headers
#include <iostream>
#include <string>

// GUI class for Window
class GUI
{
public:
    // Intialises the ImGui instance
    GUI(GLFWwindow *window, int major, int minor);
    // Terminates the UI instance
    void terminate_gui();
    // Refreshes the UI each frame
    void new_frame();
    // Renders the UI each frame
    void render_gui();

private:
};

#endif // !GUI_H
