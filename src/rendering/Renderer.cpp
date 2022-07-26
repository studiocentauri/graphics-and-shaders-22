#include "rendering/Renderer.h"

static RenderCamera rCam;

FrameBuffer::FrameBuffer()
{
}

void FrameBuffer::generate_fbo()
{
    glGenFramebuffers(1, &FBO);
}

void FrameBuffer::bind_fbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

void FrameBuffer::unbind_fbo()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::free_fbo()
{
    glDeleteFramebuffers(1, &FBO);
}

void FrameBuffer::generate_rbo()
{
    glGenRenderbuffers(1, &RBO);
}

void FrameBuffer::bind_rbo()
{
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
}

void FrameBuffer::unbind_rbo()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void FrameBuffer::free_rbo()
{
    glDeleteRenderbuffers(1, &RBO);
}

void FrameBuffer::refresh_rbo(int width, int height)
{
    bind_rbo();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    unbind_rbo();
}

void FrameBuffer::refresh_texture(int width, int height)
{
    textureColorBuffer.bind_texture();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    textureColorBuffer.unbind_texture();
}

void FrameBuffer::attach_rbo()
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

void FrameBuffer::attach_texture()
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer.id, 0);
}

void FrameBuffer::check_status()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cerr << "Frame Buffer Error. Frame Buffer not complete.\n";
    }
}

void FrameBuffer::new_frame(int width, int height)
{
    bind_fbo();
    glEnable(GL_DEPTH_TEST);
    refresh_rbo(width, height);
    refresh_texture(width, height);
}

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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE_USED);

#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void Renderer::terminate_glfw()
{
    glfwTerminate();
}

bool Renderer::create_window()
{
    bool status = true;

#if ENABLE_FULLSCREEN
    window = glfwCreateWindow(width, height, WINDOW_NAME, glfwGetPrimaryMonitor(), NULL);
#else
    window = glfwCreateWindow(width, height, WINDOW_NAME, NULL, NULL);
#endif

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        terminate_glfw();
        status = false;
    }
    return status;
}

void Renderer::setup_window_data()
{
    glfwMakeContextCurrent(window);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

#if !(ENABLE_FULLSCREEN)
#if ENABLE_FIXED_ASPECT_RATIO
    glfwSetWindowAspectRatio(window, ASPECT_RATIO_X, ASPECT_RATIO_Y);
#endif
#if ENABLE_WINDOW_BOUNDS
    glfwSetWindowSizeLimits(window, WINDOW_SIZE_LIMITS.x, WINDOW_SIZE_LIMITS.y, WINDOW_SIZE_LIMITS.z, WINDOW_SIZE_LIMITS.w);
#endif
#endif

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
}

void Renderer::setup_frame_buffer()
{
    frameBuffer.generate_fbo();
    frameBuffer.bind_fbo();
    frameBuffer.textureColorBuffer.generate_texture();
    frameBuffer.refresh_texture(width, height);
    frameBuffer.attach_texture();
    frameBuffer.generate_rbo();
    frameBuffer.bind_rbo();
    frameBuffer.refresh_rbo(width, height);
    frameBuffer.attach_rbo();
    frameBuffer.check_status();
    frameBuffer.unbind_fbo();
}

bool Renderer::close_window()
{
    return glfwWindowShouldClose(window);
}

void Renderer::swap_buffers(bool lockFrameRate)
{
    glfwSwapBuffers(window);
    glfwPollEvents();

    if (!lockFrameRate)
    {
        glfwSwapInterval(0);
    }
    else
    {
        glfwSwapInterval(1);
    }
}

bool Renderer::check_key(int key)
{
    return (glfwGetKey(window, key) == GLFW_PRESS);
}

void Renderer::start_timer()
{
    currentTime = glfwGetTime();
    previousTime = currentTime;
    deltaTime = 0.0f;
}

void Renderer::new_frame()
{
    currentTime = glfwGetTime();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

void Renderer::set_draw_mode(int mode)
{
    if (mode == 0)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
    else if (mode == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void Renderer::clear_screen(float r, float g, float b, bool depthTestEnabled)
{
    glClearColor(r, g, b, 1.0f);
    if (depthTestEnabled)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }
}

void Renderer::set_camera(Camera cam)
{
    rCam.cam = Camera(cam.position);
    rCam.isFirstMouse = true;
    rCam.lastX = width / 2.0f;
    rCam.lastY = height / 2.0f;
    rCam.xOffset = 0.0f;
    rCam.yOffset = 0.0f;
}

Camera *Renderer::get_camera()
{
    return &(rCam.cam);
}

void Renderer::set_cursor(bool status)
{
    if (status)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
}

void Renderer::process_mouse(bool isActive)
{
    if (isActive)
    {
        rCam.cam.process_mouse(rCam.xOffset, rCam.yOffset, deltaTime);
        set_cursor(false);
    }
    else
    {
        rCam.isFirstMouse = true;
        set_cursor(true);
    }

    rCam.xOffset = 0.0f;
    rCam.yOffset = 0.0f;
}

float Renderer::get_width()
{
#if ENABLE_FULLSCREEN
    return (float)WINDOW_WIDTH;
#else
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return (float)width;
#endif
}

float Renderer::get_height()
{
#if ENABLE_FULLSCREEN
    return (float)WINDOW_HEIGHT;
#else
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    return (float)height;
#endif
}

void Renderer::start_fbo_pass(float r, float g, float b)
{
    frameBuffer.unbind_fbo();
    clear_screen(r, g, b, false);
    glDisable(GL_DEPTH_TEST);
}

//------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
    if (rCam.isFirstMouse)
    {
        rCam.isFirstMouse = false;
        rCam.lastX = xpos;
        rCam.lastY = ypos;
    }
    rCam.xOffset = xpos - rCam.lastX;
    rCam.yOffset = ypos - rCam.lastY;
    rCam.lastX = xpos;
    rCam.lastY = ypos;
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    rCam.cam.process_scroll(yoffset);
}

//---------------------------------------------------------

void VertexArray::generate_buffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
}

void VertexArray::bind_vao()
{
    glBindVertexArray(VAO);
}

void VertexArray::unbind_vao()
{
    glBindVertexArray(0);
}

void VertexArray::bind_vbo(int vertexCount, GLsizeiptr stride, void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * stride, pointer, GL_STATIC_DRAW);
}

void VertexArray::unbind_vbo()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexArray::bind_ebo(int indexCount, void *pointer)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), pointer, GL_STATIC_DRAW);
}

void VertexArray::unbind_ebo()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VertexArray::set_attribute_array(int layoutLayer, int count, GLsizeiptr stride, const void *pointer)
{
    glEnableVertexAttribArray(layoutLayer);
    glVertexAttribPointer(layoutLayer, count, GL_FLOAT, GL_FALSE, stride, pointer);
}

void VertexArray::draw_triangle(int count, int startIndex)
{
    bind_vao();
    glDrawArrays(GL_TRIANGLES, startIndex, count);
    unbind_vao();
}

void VertexArray::draw_indices(int indexCount)
{
    bind_vao();
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    unbind_vao();
}

void VertexArray::free_data()
{
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}
