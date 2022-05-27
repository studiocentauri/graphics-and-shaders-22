#include <iostream>
#include "Config.h"
#include "rendering/Renderer.h"

Renderer renderer;

int main()
{
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }

    renderer.setup_window_data();

    while (!renderer.close_window())
    {
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }
        if (renderer.check_key(GLFW_KEY_R))
        {
            glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_G))
        {
            glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_B))
        {
            glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        }
        else
        {
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
