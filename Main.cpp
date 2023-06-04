#include <iostream>
#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
Renderer renderer;

// Task 3.1 defining vertices
float tr1[] = {
    -0.5f, -0.5f, 0.0f,
    0.2f, -0.5f, 0.0f,
    0.9f, 0.7f, 0.0f,
    0.0f, 0.5f, 0.0f,
    -0.8f, -0.8f, 0.0f };
unsigned int indices1[] = {
    0,1,2,0,3,4};
VertexArray varray;

int main()
{
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }

    renderer.setup_window_data();
    Shader shdr("../../shaders/defaultShader.vs", "../../shaders/defaultShader.fs");

    varray.generate_buffers();
    varray.bind_vao();
    // plotting triangles task 3.1
    varray.bind_vbo(6, 3 * sizeof(float), tr1);
    varray.bind_ebo(6, indices1);
    varray.set_attribute_array(0, 3, 3 * sizeof(float));
    varray.unbind_vbo();
    varray.unbind_vao();

    renderer.start_timer();
    while (!renderer.close_window())
    {
        renderer.new_frame();
        std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;

        // time ratio is used to vary the RGB values Task 2
        float time = (0.5*glfwGetTime() - (floor)(0.5*glfwGetTime()))*2;
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }
        if (renderer.check_key(GLFW_KEY_R))
        {
            glClearColor(1.0f*time, 0.0f, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_G))
        {
            glClearColor(0.0f, 1.0f*time, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_B))
        {
            glClearColor(0.0f, 0.0f, 1.0f*time, 1.0f);
        }
        else
        {
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing Shapes and Objects
        shdr.use();
        // varray.draw_triangle(3, 0);
        varray.draw_indices(6);
        // End of Frame
        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
