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
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
    window = glfwCreateWindow(width, height, WINDOW_NAME, NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        terminate_glfw();
        return false;
    }
    return true;
}

void Renderer::setup_window_data()
{
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
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

//------------------------------------------------------------

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
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

void VertexArray::free_data()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}