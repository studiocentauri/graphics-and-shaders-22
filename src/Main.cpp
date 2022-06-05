#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"

#include <iostream>

Renderer renderer;

// float vertices[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f, 0.5f, 0.0f};

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f};

// float vertices[] = {
//     -0.5f, 0.5f, 0.0f,
//     0.5f, 0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     -0.5f, -0.5f, 0.0f};

// unsigned int indices[] = {
//     0, 1, 2,
//     2, 3, 0};

VertexArray varray;
int main()
{
    // Setup Renderer
    renderer.initialise_glfw();
    if (!renderer.create_window())
    {
        return -1;
    }
    renderer.setup_window_data();

    // Setup Vertex Array
    varray.generate_buffers();
    varray.bind_vao();
    varray.bind_vbo(3, 8 * sizeof(float), vertices);
    // varray.bind_ebo(6, indices);
    varray.set_attribute_array(0, 3, 8 * sizeof(float));
    varray.set_attribute_array(1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    varray.set_attribute_array(2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    varray.unbind_vbo();
    varray.unbind_vao();

    // Setup Shaders and Textures
    Shader shdr(FileSystem::get_path("shaders/textureShader.vs").c_str(), FileSystem::get_path("shaders/textureShader.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/iitk_logo.png"));

    // Setup Data
    float totalTime = 0;
    float xAxis = 0, yAxis = 0;
    float translationSpeed = 1.0f;

    // Start Render Loop
    renderer.start_timer();
    while (!renderer.close_window())
    {
        // Frame Start
        renderer.new_frame();
        totalTime += renderer.deltaTime;
        totalTime = (totalTime > 1.0f) ? (totalTime - 1.0f) : totalTime;
        // std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;

        // Check for Inputs
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }

        // Setup Background Color
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

        // Set Draw Mode
        if (renderer.check_key(GLFW_KEY_P))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        else if (renderer.check_key(GLFW_KEY_L))
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // Move Asset
        if (renderer.check_key(GLFW_KEY_W))
        {
            yAxis += translationSpeed * renderer.deltaTime;
        }
        if (renderer.check_key(GLFW_KEY_S))
        {
            yAxis -= translationSpeed * renderer.deltaTime;
        }
        if (renderer.check_key(GLFW_KEY_D))
        {
            xAxis += translationSpeed * renderer.deltaTime;
        }
        if (renderer.check_key(GLFW_KEY_A))
        {
            xAxis -= translationSpeed * renderer.deltaTime;
        }

        // Setup Shader Uniforms
        shdr.use();
        glUniform1f(glGetUniformLocation(shdr.id, "Time"), totalTime);
        glUniform1f(glGetUniformLocation(shdr.id, "XAxis"), xAxis);
        glUniform1f(glGetUniformLocation(shdr.id, "YAxis"), yAxis);
        tex.bind_texture();

        // Drawing Shapes and Objects
        shdr.use();
        varray.draw_triangle(3, 0);
        // varray.draw_indices(6);

        // End of Frame
        renderer.swap_buffers(false);
    }

    // Free Date and stop processes
    renderer.terminate_glfw();
    shdr.free_data();
    varray.free_data();
    return 0;
}
