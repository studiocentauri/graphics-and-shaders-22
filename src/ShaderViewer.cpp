// Third-party Headers
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

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

// Application Data
float totalTime = 0;
ImVec4 bkgColor(35.0f / 255.0f, 60.0f / 255.0f, 75.0f / 255.0f, 1.0f);
const char *drawOptions[3] = {"Point", "Line", "Fill"};
int drawOption = 2;
bool showFrameRate = true;
bool lockFrameRate = true;
int FPS = 0;
float FPSfrequency = 3;
float timer = 1;

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
    Shader shdr(FileSystem::get_path("shaders/2dshaders/shaderViewer.vs").c_str(), FileSystem::get_path("shaders/2dshaders/shaderViewer.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/marble.jpg"));

    // Start Render Loop
    renderer.start_timer();
    while (!renderer.close_window())
    {
        // New Renderer Frame
        renderer.new_frame();
        totalTime += renderer.deltaTime;
        timer += renderer.deltaTime;
        if (timer >= 1 / FPSfrequency)
        {
            timer = 0.0f;
            FPS = (int)(1 / renderer.deltaTime);
        }
        totalTime = (totalTime > 300.0f) ? (totalTime - 300.0f) : totalTime;

        // New UI Frame
        gui.new_frame();

        // Process Scene
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }

        // Do Calculations
        int currentWidth = (int)(renderer.get_width());
        int currentHeight = (int)(renderer.get_height());
        if (currentHeight == 0 || currentWidth == 0)
        {
            currentHeight = 1.0f;
            currentWidth = 1.0f;
        }

        // Set Draw Mode
        renderer.set_draw_mode(drawOption);

        // Clear Previous Frame
        renderer.clear_screen(bkgColor.x, bkgColor.y, bkgColor.z);

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
        ImGui::Begin("Viewer UI");
        ImGui::ColorEdit3("Background Color", &bkgColor.x);
        ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
        ImGui::Checkbox("VSync", &lockFrameRate);
        ImGui::Checkbox("Show FPS", &showFrameRate);
        ImGui::SliderFloat("FPS Update Frequency", &FPSfrequency, 0.5f, 60.0f);
        if (showFrameRate)
        {
            ImGui::Text("%d FPS", FPS);
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
