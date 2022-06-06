#include <iostream>
#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
Renderer renderer;
// float vertices[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f, 0.5f, 0.0f};
float vertices[] = {
    -0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.0f,0.0f,0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f};
unsigned int indices[] = {
    0, 1, 2,
    2, 3, 4 } ;
VertexArray varray1,varray2;

int main()
{
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }

    renderer.setup_window_data();
    Shader shdr("../../shaders/defaultShader.vs", "../../shaders/defaultShader.fs");

    varray1.generate_buffers();
    varray1.bind_vao();
    varray1.bind_vbo(5, 3 * sizeof(float), vertices);
    varray1.bind_ebo(3, indices);
    varray1.set_attribute_array(0, 3, 3 * sizeof(float));
    varray1.unbind_vbo();
    varray1.unbind_vao();

    varray2.generate_buffers();
    varray2.bind_vao();
    varray2.bind_vbo(5, 3 * sizeof(float), vertices);
    varray2.bind_ebo(3, indices+3);
    varray2.set_attribute_array(0, 3, 3 * sizeof(float));
    varray2.unbind_vbo();
    varray2.unbind_vao();

    float r_i = 1 , b_i = 1 , g_i = 1 , delta = 0;               // indexes for changing bg color with time
    renderer.start_timer();
    while (!renderer.close_window())
    {
        renderer.new_frame();
        std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }
        if (renderer.check_key(GLFW_KEY_R))
        {
            if(r_i >=1)
            {
                delta = -0.001;
            }
            else if(r_i <=0)
            {
                delta = 0.001;
            }
            r_i += delta ;
            glClearColor ( r_i, 0.0f, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_G))
        {
             if(g_i >=1)
            {
                delta = -0.001;
            }
            else if(g_i <=0)
            {
                delta = 0.001;
            }
            g_i += delta ;
            glClearColor(0.0f, g_i, 0.0f, 1.0f);
        }
        else if (renderer.check_key(GLFW_KEY_B))
        {   
             if(b_i >=1)
            {
                delta = -0.001;
            }
            else if(b_i <=0)
            {
                delta = 0.001;
            }
            b_i += delta ;
            glClearColor(0.0f, 0.0f, b_i, 1.0f);
        }
        else
        {
            r_i = 0, b_i = 0 , g_i = 0 ;
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        }
        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing Shapes and Objects
        shdr.use();
        // varray.draw_triangle(3, 0);
        varray1.draw_indices(3);
        varray2.draw_indices(3);
        // End of Frame
        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
