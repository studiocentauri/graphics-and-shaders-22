#include <iostream>
#include "Config.h"
#include "rendering/Renderer.h"

Renderer renderer;

int main()
{
    renderer.initialise_glfw();
    if(!renderer.create_window())
    {
        return -1;
    }

    renderer.setup_window_data();

    while(!renderer.close_window())
    {
        renderer.swap_buffers(false);
        glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    renderer.terminate_glfw();
    return 0;
}

