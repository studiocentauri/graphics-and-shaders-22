#ifndef RENDERER_H
#define RENDERER_H

// Third-party Headers
#include "thirdparty/glad/glad.h"
#include "thirdparty/GLFW/glfw3.h"

// Custom Headers
#include "Config.h"
#include "rendering/Camera.h"

// Standard Headers
#include <iostream>

// Struct for Renderer's Camera
struct RenderCamera
{
    Camera cam;    // Camera instance
    float lastX;   // Last Pos of cursor along X
    float lastY;   // Last Pos of cursor along Y
    float xOffset; // Offset of cursor since last frame along X
    float yOffset; // Offset of cursor since last frame along Y
};

// Vertex Array Class
class VertexArray
{
private:
    unsigned int VAO; // Vertex Array Object
    unsigned int VBO; // Vertex Buffer Object
    unsigned int EBO; // Element Buffer Object

public:
    // Generates the vertex buffer objects
    void generate_buffers();
    // Bind the current VAO to Renderer
    void bind_vao();
    // Binds the current VBO to Renderer
    void bind_vbo(int vertexCount, GLsizeiptr stride, void *pointer);
    // Binds the current EBO to Renderer
    void bind_ebo(int indexCount, void *pointer);
    // Unbinds the current VAO from Renderer
    void unbind_vao();
    // Unbinds the current VBO from Renderer
    void unbind_vbo();
    // Unbinds the current EBO from Renderer
    void unbind_ebo();
    // Sets Vertex Data for a given layout
    void set_attribute_array(int layoutLayer, int count, GLsizeiptr stride, const void *pointer = (void *)0);
    // Draws using vertices
    void draw_triangle(int count, int startIndex);
    // Draws using indices
    void draw_indices(int indexCount);
    // Frees vertex buffer objects
    void free_data();
};

// Renderer Class for Window
class Renderer
{
private:
    float previousTime; // Time of previous frame
    float currentTime;  // Time of current frame

public:
    int major;          // Major version of OpenGL
    int minor;          // Minor version of OpenGL
    int width;          // Start width of window
    int height;         // Start height of window
    float deltaTime;    // Delta Time for current frame
    GLFWwindow *window; // Window instance for Renderer

    // Default Renderer Constructor
    Renderer(int major_ = OPENGL_MAJOR_VERSION, int minor_ = OPENGL_MINOR_VERSION, int width_ = WINDOW_WIDTH, int height_ = WINDOW_HEIGHT);
    // Intialises GLFW with opengl settings
    void initialise_glfw();
    // Terminates the GLFW context
    void terminate_glfw();
    // Creates the window instance
    bool create_window();
    // Setups the window Data
    void setup_window_data();
    // Checks whether to close window
    bool close_window();
    // Swaps the window buffers and ends the frame
    void swap_buffers(bool lockFrameRate);
    // Checks for input
    bool check_key(int key);
    // Start the Renderer timer
    void start_timer();
    // Refresh the timer each frame
    void new_frame();
    // Sets the camera instance
    void set_camera(Camera cam);
    // Returns the camera instance
    Camera *get_camera();
    // Sets the cursor to status
    void set_cursor(bool status);
    // Processes cursor motion for cam
    void process_mouse(bool isActive);
};

// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// Callback function for cursor motion
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
// Callback function for scroll motion
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

#endif // !RENDERER_H
