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
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f};

// Vertex data for two triangles with common vertex

float tri1[] = {
    -0.6f, 0.25f, 0.0f,
    -0.6f, -0.5f, 0.0f,
    0.0f, 0.0f, 0.0f // common vertex
};

float tri2[] = { 
    0.0f, 0.0f, 0.0f, // common vertex
    0.6f, 0.5f, 0.0f,
    0.6f, -0.5f, 0.0f,
};

unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0};
VertexArray varray;

int main()
{
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }

    renderer.setup_window_data();
    //Shader shdr("../../shaders/defaultShader.vs", "../../shaders/defaultShader.fs"); // Incorrect path
    Shader shdr("../shaders/defaultShader.vs", "../shaders/defaultShader.fs");
   
    // Creating a new shader for different colour

    Shader shdr2("../shaders/defaultShader.vs", "../shaders/newShader.fs");

    varray.generate_buffers();
    varray.bind_vao();
    //varray.bind_vbo(4, 3 * sizeof(float), vertices);
    varray.bind_vbo(3, 3 * sizeof(float), tri1);
    //varray.bind_ebo(6, indices);
    //varray.bind_ebo(3, tri1);
    //varray.set_attribute_array(0, 3, 3 * sizeof(float));
    varray.set_attribute_array(0, 3, 3 * sizeof(float));
    varray.unbind_vbo();
    varray.unbind_vao();


    renderer.start_timer();
    while (!renderer.close_window())
    {
        renderer.new_frame();
        std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;

        static int cs = 0;
        if (renderer.check_key(GLFW_KEY_R))
        {
            //glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // unmodified code
            std::cout << "PRESSED R\n";
            if (cs == 1) cs = 0;
            else cs = 1;
        }
        else if (renderer.check_key(GLFW_KEY_G))
        {
            //glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
            std::cout << "PRESSED G\n";
            if (cs == 2) cs = 0;
            else cs = 2;
        }
        else if (renderer.check_key(GLFW_KEY_B))
        {
            std::cout << "PRESSED B\n";
            //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
            if (cs == 3) cs = 0;
            else cs = 3;
        }
        else
        {
            std::cout << "NOTHING\n";
            cs = cs;
            //glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
        }

        std::cout << "cs now " << cs << " \n"; // For debugging

        switch (cs) {
        case 0:
            glClearColor(0.2f, 0.1f, 0.3f, 1.0f);
            break;

        case 1:
            glClearColor((1 + (sin(glfwGetTime()))) / 2, 0.1f, 0.3f, 1.0f);
            break;

        case 2:
            glClearColor(0.2f, (1 + (sin(glfwGetTime()))) / 2, 0.3f, 1.0f);
            break;

        case 3:
            glClearColor(0.2f, 0.1f, (1 + (sin(glfwGetTime()))) / 2, 1.0f);
            break;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        // Drawing Shapes and Objects
        shdr.use();
        // varray.draw_triangle(3, 0);
        varray.bind_vbo(3, 3 * sizeof(float), tri1);
        varray.draw_triangle(3, 0);

        shdr2.use();
        varray.set_attribute_array(0, 3, 3 * sizeof(float));
        varray.bind_vbo(3, 3 * sizeof(float), tri2);
        varray.draw_triangle(3, 0);

        //varray.draw_indices(6);
        // End of Frame
        renderer.swap_buffers(false);
    }

    renderer.terminate_glfw();
    return 0;
}
