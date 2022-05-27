#include "rendering/Renderer.h"

Renderer::Renderer(int major_, int minor_, int width_, int height_)
{
    major = major_;
    minor = minor_;
    width = width_;
    height = height_;
}

void Renderer::initialise_glfw()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif
}

void Renderer::terminate_glfw()
{
    glfwTerminate();
}