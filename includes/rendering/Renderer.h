#ifndef RENDERER_H
#define RENDERER_H

#include "rendering/Camera.h"
#include "Config.h"
#include "thirdparty/glad/glad.h"
#include "thirdparty/GLFW/glfw3.h"

#include <iostream>

// Struct for callback
struct RenderCamera
{
    Camera cam;
    float lastX, lastY;
    bool isFirstMouse;
    float xOffset, yOffset;
};

// Vertex Array Class
class VertexArray
{
private:
    unsigned int VAO, VBO, EBO;

public:
    void generate_buffers();
    void bind_vao();
    void bind_vbo(int vertexCount, GLsizeiptr stride, void *pointer);
    void bind_ebo(int indexCount, void *pointer);
    void unbind_vao();
    void unbind_vbo();
    void unbind_ebo();
    void set_attribute_array(int layoutLayer, int count, GLsizeiptr stride, const void *pointer = (void *)0);
    void draw_triangle(int count, int startIndex);
    void draw_indices(int indexCount);
    void free_data();
};

// Rendering Class
class Renderer
{
private:
    float previousTime;
    float currentTime;

public:
    int major;
    int minor;
    int width;
    int height;
    float deltaTime;
    GLFWwindow *window;

    Renderer(int major_ = OPENGL_MAJOR_VERSION, int minor_ = OPENGL_MINOR_VERSION, int width_ = WINDOW_WIDTH, int height_ = WINDOW_HEIGHT);
    void initialise_glfw();
    void terminate_glfw();
    bool create_window();
    void setup_window_data();
    bool close_window();
    void swap_buffers(bool lockFrameRate);
    bool check_key(int key);
    void start_timer();
    void new_frame();
    void set_camera(Camera cam);
    Camera *get_camera();
    void set_mouse();
};

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif
