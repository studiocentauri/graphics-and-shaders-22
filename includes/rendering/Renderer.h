#ifndef RENDERER_H
#define RENDERER_H

// Third-party Headers
#include "glad/glad.h"
#include "GLFW/glfw3.h"

// Custom Headers
#include "Config.h"
#include "rendering/Camera.h"
#include "rendering/Texture.h"

// Standard Headers
#include <iostream>

// Struct for Renderer's Camera
struct RenderCamera
{
    Camera cam;        // Camera instance
    bool isFirstMouse; // Flag for the first callback
    float lastX;       // Last Pos of cursor along X
    float lastY;       // Last Pos of cursor along Y
    float xOffset;     // Offset of cursor since last frame along X
    float yOffset;     // Offset of cursor since last frame along Y
};

// Framebuffer class for Renderer
class FrameBuffer
{
public:
    unsigned int FBO;           // Frame buffer object
    unsigned int RBO;           // Render buffer object
    Texture textureColorBuffer; // Texture to store framebuffer data

    // Default Framebuffer constructor
    FrameBuffer();
    // Generates the FBO in memory
    void generate_fbo();
    // Binds the FBO in memory
    void bind_fbo();
    // Unbinds the FBO from memory
    void unbind_fbo();
    // Frees the FBO from memory
    void free_fbo();
    // Generates RBO in memory
    void generate_rbo();
    // Binds the RBO in memory
    void bind_rbo();
    // Unbinds the RBO from memory
    void unbind_rbo();
    // Ubnbinds the RBO from memory
    void free_rbo();
    // Refreshes the RBO based on screen resolution
    void refresh_rbo(int width, int height);
    // Refreshes the texture based on screen resolution
    void refresh_texture(int width, int height);
    // Attaches RBO to FBO
    void attach_rbo();
    // Attaches texture to FBO
    void attach_texture();
    // Refreshes the FBO at start of each frame
    void new_frame(int width, int height);
    // Checks if Framebuffer created sucessfully
    void check_status();

private:
};

// Renderer Class for Window
class Renderer
{
private:
    float previousTime; // Time of previous frame
    float currentTime;  // Time of current frame

public:
    int major;               // Major version of OpenGL
    int minor;               // Minor version of OpenGL
    int width;               // Start width of window
    int height;              // Start height of window
    float deltaTime;         // Delta Time for current frame
    GLFWwindow *window;      // Window instance for Renderer
    FrameBuffer frameBuffer; // Framebuffer for the Renderer

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
    // FrameBuffer Setup
    void setup_frame_buffer();
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
    // Sets the draw mode
    void set_draw_mode(int mode = 2);
    // Clears the background color with a color
    void clear_screen(float r, float g, float b, bool depthTestEnabled = true);
    // Sets the camera instance
    void set_camera(Camera cam);
    // Returns the camera instance
    Camera *get_camera();
    // Sets the cursor to status
    void set_cursor(bool status);
    // Processes cursor motion for cam
    void process_mouse(bool isActive);
    // Get current height of screen
    float get_width();
    // Get current width of screen
    float get_height();
    // Starts the FBO Render pass
    void start_fbo_pass(float r, float g, float b);
};

// Callback function for window resizing
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
// Callback function for cursor motion
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
// Callback function for scroll motion
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

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

#endif // !RENDERER_H
