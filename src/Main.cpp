#include "Config.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"
#include "object/Transform.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

#include <iostream>

Renderer renderer;
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// float vertices[] = {
//     -0.866f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//     0.866f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//     0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f};

// float vertices[] = {
//     -0.5f, 0.5f, 0.0f,
//     0.5f, 0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     -0.5f, -0.5f, 0.0f};

// unsigned int indices[] = {
//     0, 1, 2,
//     2, 3, 0};

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

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
    renderer.set_camera(camera);
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
    varray.bind_vbo(36, 5 * sizeof(float), vertices);
    // varray.bind_ebo(6, indices);
    varray.set_attribute_array(0, 3, 5 * sizeof(float));
    varray.set_attribute_array(1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    varray.unbind_vbo();
    varray.unbind_vao();

    // Setup Shaders and Textures
    Shader shdr(FileSystem::get_path("shaders/3dshaders/colorShader.vs").c_str(), FileSystem::get_path("shaders/3dshaders/textureShader.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/iitk_logo.png"));
    Texture tex1(FileSystem::get_path("resources/textures/logo4.png"));
    Texture tex2(FileSystem::get_path("resources/textures/council_logo.png"));

    // Setup Data
    float totalTime = 0;
    Transform transforms[] = {Transform(glm::vec3(0.0f, 0.0f, -5.0f)),
                              Transform(glm::vec3(1.0f, 0.0f, -4.0f)),
                              Transform(glm::vec3(-1.0f, 0.0f, -3.0f)),
                              Transform(glm::vec3(0.0f, 1.0f, -2.0f)),
                              Transform(glm::vec3(0.0f, -1.0f, -1.0f))};
    // float xAxis = 0, yAxis = 0;
    // float translationSpeed = 1.0f;
    // float rotation = 0;
    // glm::vec3 positions[] = {glm::vec3(0.0f, 0.0f, -5.0f),
    //                          glm::vec3(1.0f, 0.0f, -4.0f),
    //                          glm::vec3(-1.0f, 0.0f, -3.0f),
    //                          glm::vec3(0.0f, 1.0f, -2.0f),
    //                          glm::vec3(0.0f, -1.0f, -1.0f)};

    // glm::vec3 scale = glm::vec3(1.0f);
    ImVec4 objectColor(1.0f, 1.0f, 1.0f, 1.0f);
    ImVec4 bkgColor(0.2f, 0.3f, 0.2f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    int drawOption = 2;
    bool isPerspective = true;
    bool freeRoam = false;
    bool showFrameRate = false;
    bool lockFrameRate = false;
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
        if (renderer.check_key(GLFW_KEY_SPACE))
        {
            freeRoam = true;
        }
        if (renderer.check_key(GLFW_KEY_LEFT_SHIFT))
        {
            freeRoam = false;
        }
        if (freeRoam)
        {
            if (renderer.check_key(GLFW_KEY_W))
            {
                renderer.get_camera()->process_keyboard(CAM_FORWARD, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_S))
            {
                renderer.get_camera()->process_keyboard(CAM_BACKWARD, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_A))
            {
                renderer.get_camera()->process_keyboard(CAM_LEFT, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_D))
            {
                renderer.get_camera()->process_keyboard(CAM_RIGHT, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_Q))
            {
                renderer.get_camera()->process_keyboard(CAM_UP, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_E))
            {
                renderer.get_camera()->process_keyboard(CAM_DOWN, renderer.deltaTime);
            }
        }
        renderer.process_mouse(freeRoam);

        // Setup Background Color
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

        glm::mat4 view = renderer.get_camera()->get_view_matrix();

        glm::mat4 projection(1.0f);
        int currentWidth, currentHeight;
        glfwGetWindowSize(renderer.window, &currentWidth, &currentHeight);
        if (currentHeight == 0 || currentWidth == 0)
        {
            currentHeight = 1.0f;
            currentWidth = 1.0f;
        }
        if (isPerspective)
        {
            projection = glm::perspective((float)glm::radians(renderer.get_camera()->fieldOfView), (((float)currentWidth) / ((float)currentHeight)), 0.1f, 100.0f);
        }
        else
        {
            float aspect = (((float)currentWidth) / ((float)currentHeight));
            float camSize = 5.0f;
            glm::vec2 camDim(aspect * camSize, camSize);
            projection = glm::ortho(-camDim.x / 2.0f, camDim.x / 2.0f, -camDim.y / 2.0f, camDim.y / 2.0f, 0.01f, 100.0f);
        }

        // Setup Shader Uniforms
        shdr.use();
        shdr.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
        shdr.set_float("Time", totalTime);
        shdr.set_mat4("view", view);
        shdr.set_mat4("projection", projection);
        shdr.set_texture("tex", &tex);
        // shdr.set_texture("tex1", &tex2);

        // Drawing Shapes and Objects
        shdr.use();
        set_active_texture(0);
        for (int i = 0; i < 5; i++)
        {
            shdr.set_mat4("model", transforms[i].get_model_matrix());
            varray.draw_triangle(36, 0);
        }

        if (!freeRoam)
        {
            // Setup UI Windows
            ImGui::Begin("UI Box");
            ImGui::ColorEdit3("Object Color", &objectColor.x);
            ImGui::ColorEdit3("Background Color", &bkgColor.x);
            ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
            ImGui::Checkbox("VSync", &lockFrameRate);
            ImGui::Checkbox("Show FPS", &showFrameRate);
            if (showFrameRate)
            {
                ImGui::Text("%d FPS", (int)(1 / renderer.deltaTime));
            }
            ImGui::End();
            // Object Property UI
            ImGui::Begin("Object Property");
            for (int i = 0; i < 5; i++)
            {
                ImGui::Text("Object %d : ", i);
                ImGui::SliderFloat3(("Position##" + std::to_string(i) + " : ").c_str(), &(transforms[i].position.x), -15.5f, 15.5f);
                ImGui::SliderFloat3(("Rotation##" + std::to_string(i) + " : ").c_str(), &(transforms[i].rotation.x), -180.0f, 180.0f);
                ImGui::SliderFloat3(("Scale##" + std::to_string(i) + " : ").c_str(), &(transforms[i].scale.x), -5.0f, 5.0f);
                if (ImGui::Button(("Reset Transforms##" + std::to_string(i) + " : ").c_str()))
                {
                    transforms[i].reset_transform();
                }
            }
            ImGui::Checkbox("IsPerspective", &isPerspective);
            ImGui::End();
        }

        // Draw UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // End of Frame
        renderer.swap_buffers(lockFrameRate);
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
