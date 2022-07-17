// Third-party Headers
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

// Custom Headers
#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"
#include "gui/GUI.h"

// Standard Headers
#include <iostream>

// Renderer Data Setup
//----------------------
Renderer renderer;

float vertices[] = {
    -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f};

unsigned int indices[] = {
    0, 2, 1,
    2, 0, 3};

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

    // Setting up imgui
    GUI gui(renderer.window, renderer.major, renderer.minor);

    // Setup Vertex Array
    varray.generate_buffers();
    varray.bind_vao();
    varray.bind_vbo(4, 5 * sizeof(float), vertices);
    varray.bind_ebo(6, indices);
    varray.set_attribute_array(0, 3, 5 * sizeof(float));
    varray.set_attribute_array(1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    varray.unbind_vbo();
    varray.unbind_vao();

    // Setup Shaders and Textures
    Shader shdr(FileSystem::get_path("shaders/2dshaders/shaderToy.vs").c_str(), FileSystem::get_path("shaders/2dshaders/shaderToy.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/marble.jpg"));

    // Setup Data
    float totalTime = 0;
    ImVec4 bkgColor(0.2f, 0.3f, 0.2f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    int drawOption = 2;
    bool showFrameRate = true;
    bool lockFrameRate = true;

    // Start Render Loop
    renderer.start_timer();
    while (!renderer.close_window())
    {
        // Frame Start
        renderer.new_frame();
        totalTime += renderer.deltaTime;
        totalTime = (totalTime > 300.0f) ? (totalTime - 300.0f) : totalTime;

        // New UI Frame
        gui.new_frame();

        // Check for Inputs
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }

        // Clear Previous Frame
        glClearColor(bkgColor.x, bkgColor.y, bkgColor.z, bkgColor.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set Draw Mode
        if (drawOption == 0)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        }
        else if (drawOption == 1)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // Do Calculations
        int currentWidth, currentHeight;
        glfwGetWindowSize(renderer.window, &currentWidth, &currentHeight);
        if (currentHeight == 0 || currentWidth == 0)
        {
            currentHeight = 1.0f;
            currentWidth = 1.0f;
        }

        // Setup Shader Uniforms
        shdr.use();
        shdr.set_float("iTime", totalTime);
        shdr.set_float("iTimeDelta", renderer.deltaTime);
        shdr.set_vec2("iResolution", currentWidth, currentHeight);
        shdr.set_texture("iChannel0", &tex);

        // Drawing Shapes and Objects
        shdr.use();
        set_active_texture(0);
        varray.draw_indices(6);

        // Setup UI Windows
        ImGui::Begin("UI Box");
        ImGui::ColorEdit3("Background Color", &bkgColor.x);
        ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
        ImGui::Checkbox("VSync", &lockFrameRate);
        ImGui::Checkbox("Show FPS", &showFrameRate);
        if (showFrameRate)
        {
            ImGui::Text("%d FPS", (int)(1 / renderer.deltaTime));
        }
        ImGui::End();

        // Draw UI
        gui.render_gui();

        // End of Frame
        renderer.swap_buffers(lockFrameRate);
    }

    // Free Date and stop processes
    gui.terminate_gui();

    shdr.free_data();
    varray.free_data();
    renderer.terminate_glfw();
    return 0;
}
