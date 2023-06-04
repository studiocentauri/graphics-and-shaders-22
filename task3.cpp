    #include <GLFW/glfw3.h>

const int MIN_WIDTH = 200;
const int MIN_HEIGHT = 150;
const int MAX_WIDTH = 1920;
const int MAX_HEIGHT = 1080;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Enforce minimum and maximum sizes
    int newWidth = width;
    int newHeight = height;

    if (newWidth < MIN_WIDTH)
        newWidth = MIN_WIDTH;
    if (newHeight < MIN_HEIGHT)
        newHeight = MIN_HEIGHT;
    if (newWidth > MAX_WIDTH)
        newWidth = MAX_WIDTH;
    if (newHeight > MAX_HEIGHT)
        newHeight = MAX_HEIGHT;

    // Set the new window size
    glfwSetWindowSize(window, newWidth, newHeight);

    // Adjust the viewport to match the new size
    glViewport(0, 0, newWidth, newHeight);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Set the framebuffer size callback */
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
