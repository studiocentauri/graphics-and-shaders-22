#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

#include <iostream>

Renderer renderer;

// float vertices[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f, 0.5f, 0.0f};

float vertices[] = {
    -0.866f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.866f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f};

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
    // Setting up imgui
    std::string versionText = "#version " + std::to_string(renderer.major) + std::to_string(renderer.minor) + "0";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(renderer.window, true);
    ImGui_ImplOpenGL3_Init(versionText.c_str());
    // Render ImGui
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    ImGui::StyleColorsDark();

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
    Shader shdr(FileSystem::get_path("shaders/3dshaders/colorShader.vs").c_str(), FileSystem::get_path("shaders/3dshaders/colorShader.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/iitk_logo.png"));
    Texture tex1(FileSystem::get_path("resources/textures/logo4.png"));
    Texture tex2(FileSystem::get_path("resources/textures/council_logo.png"));

    // Setup Data
    float totalTime = 0;
    float xAxis = 0, yAxis = 0;
    float translationSpeed = 1.0f;
    float rotation = 0;
    glm::vec3 centroid = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec2 scale = glm::vec2(1.0f);
    ImVec4 objectColor(0.8f, 0.5f, 0.2f, 1.0f);
    ImVec4 bkgColor(0.2f, 0.3f, 0.2f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    int drawOption = 2;
    // Start Render Loop
    renderer.start_timer();
    while (!renderer.close_window())
    {
        // Frame Start
        renderer.new_frame();
        totalTime += renderer.deltaTime;
        totalTime = (totalTime > 1.0f) ? (totalTime - 1.0f) : totalTime;
        // std::cout << renderer.deltaTime << " " << (int)(1.0f / renderer.deltaTime) << std::endl;
        // New UI Frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Check for Inputs
        if (renderer.check_key(GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(renderer.window, true);
        }

        // Setup Background Color
        glClearColor(bkgColor.x, bkgColor.y, bkgColor.z, bkgColor.w);
        glClear(GL_COLOR_BUFFER_BIT);

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
        glm::mat4 model(1.0f);
        model = glm::translate(model, centroid);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(scale, 1.0f));

        glm::mat4 view(1.0f);

        glm::mat4 projection(1.0f);
        int currentWidth, currentHeight;
        glfwGetWindowSize(renderer.window, &currentWidth, &currentHeight);
        projection = glm::perspective((float)glm::radians(60.0f), (((float)currentWidth)/((float)currentHeight)), 0.1f, 100.0f);

        // Setup Shader Uniforms
        shdr.use();
        shdr.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
        shdr.set_float("Time", totalTime);
        shdr.set_vec2("offset", xAxis, yAxis);
        shdr.set_mat4("model", model);
        shdr.set_mat4("view", view);
        shdr.set_mat4("projection", projection);
        shdr.set_texture("tex", &tex);
        shdr.set_texture("tex1", &tex2);

        // Drawing Shapes and Objects
        shdr.use();
        set_active_texture(0);
        varray.draw_triangle(3, 0);
        // varray.draw_indices(6);
        // Setup UI Windows
        ImGui::Begin("UI Box");
        ImGui::ColorEdit3("Object Color", &objectColor.x);
        ImGui::ColorEdit3("Background Color", &bkgColor.x);
        ImGui::SliderFloat("SliderX", &xAxis, -0.5f, 0.5f);
        ImGui::SliderFloat("SliderY", &yAxis, -0.5f, 0.5f);
        ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
        ImGui::End();
        // Object Property UI
        ImGui::Begin("Object Property");
        ImGui::SliderFloat("Rotation", &rotation, -180.0f, 180.0f);
        ImGui::SliderFloat3("Position", &centroid.x, -0.5f, 0.5f);
        ImGui::SliderFloat2("Scale", &scale.x, -3.0f, 3.0f);
        ImGui::End();

        // Draw UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // End of Frame
        renderer.swap_buffers(false);
    }

    // Free Date and stop processes
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    shdr.free_data();
    varray.free_data();
    renderer.terminate_glfw();
    return 0;
}
