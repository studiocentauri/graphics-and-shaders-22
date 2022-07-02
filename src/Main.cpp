// Third-party Headers
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

// Custom Headers
#include "Config.h"
#include "rendering/Camera.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"
#include "object/Transform.h"
#include "object/Actor.h"

// Standard Headers
#include <iostream>
#include <vector>

// Renderer Data Setup
//----------------------
Renderer renderer;
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

// float vertices[] = {
//     -0.866f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//     0.866f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
//     0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f};

float vertices[] = {
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f};

VertexArray varray;
std::vector<RenderActor> actors;
std::vector<RenderActor> lightActors;
std::vector<LightSource> lights;

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
    varray.bind_vbo(36, 8 * sizeof(float), vertices);
    // varray.bind_ebo(6, indices);
    varray.set_attribute_array(0, 3, 8 * sizeof(float));
    varray.set_attribute_array(1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    varray.set_attribute_array(2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    varray.unbind_vbo();
    varray.unbind_vao();

    // Setup Shaders and Textures
    Shader shdr(FileSystem::get_path("shaders/3dshaders/lighting.vs").c_str(), FileSystem::get_path("shaders/3dshaders/lighting.fs").c_str());
    Shader lightshdr(FileSystem::get_path("shaders/3dshaders/colorShader.vs").c_str(), FileSystem::get_path("shaders/3dshaders/colorShader.fs").c_str());
    Texture tex(FileSystem::get_path("resources/textures/iitk_logo.png"));

    // Setup Data
    float totalTime = 0;
    Transform transforms[] = {Transform(glm::vec3(0.0f, 0.0f, -5.0f)),
                              Transform(glm::vec3(1.5f, 1.0f, -4.0f)),
                              Transform(glm::vec3(-1.0f, -1.0f, -3.0f)),
                              Transform(glm::vec3(-2.0f, 2.0f, -2.0f)),
                              Transform(glm::vec3(2.0f, -2.0f, -1.0f))};

    for (int i = 0; i < 5; i++)
    {
        RenderActor Ac("Cube" + std::to_string(i));
        Material mat(glm::vec3(245.0f / 255.0f, 160.0f / 255.0f, 130.0f / 255.0f), glm::vec3(245.0f / 255.0f, 160.0f / 255.0f, 130.0f / 255.0f), glm::vec3(1.0f));
        Ac.mat = mat;
        Ac.tr = transforms[i];
        actors.push_back(Ac);
    }

    Transform lightstr[] = {Transform(glm::vec3(0.7f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.2f))};

    for (int i = 0; i < 1; i++)
    {
        RenderActor rc("Light" + std::to_string(i));
        Material mat(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f));
        rc.mat = mat;
        rc.tr = lightstr[i];
        lightActors.push_back(rc);
    }

    for (int i = 0; i < lightActors.size(); i++)
    {
        LightSource ls;
        ls.position = lightActors[i].tr.position;
        lights.push_back(ls);
    }

    ImVec4 bkgColor(135.0f / 255.0f, 225.0f / 255.0f, 222.0f / 255.0f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    int drawOption = 2;
    bool isPerspective = true;
    bool freeRoam = false;
    bool showFrameRate = false;
    bool lockFrameRate = true;

    // Start Render Loop
    renderer.start_timer();
    while (!renderer.close_window())
    {
        // Frame Start
        renderer.new_frame();
        totalTime += renderer.deltaTime;
        totalTime = (totalTime > 1.0f) ? (totalTime - 1.0f) : totalTime;

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
            if (renderer.check_key(GLFW_KEY_E))
            {
                renderer.get_camera()->process_keyboard(CAM_UP, renderer.deltaTime);
            }
            if (renderer.check_key(GLFW_KEY_Q))
            {
                renderer.get_camera()->process_keyboard(CAM_DOWN, renderer.deltaTime);
            }
        }
        renderer.process_mouse(freeRoam);

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
            projection = glm::perspective((float)glm::radians(renderer.get_camera()->fieldOfView), (((float)currentWidth) / ((float)currentHeight)), CAMERA_NEAR_PLANE, CAMERA_FAR_PLANE);
        }
        else
        {
            float aspect = (((float)currentWidth) / ((float)currentHeight));
            float camSize = 5.0f;
            glm::vec2 camDim(aspect * camSize, camSize);
            projection = glm::ortho(-camDim.x / 2.0f, camDim.x / 2.0f, -camDim.y / 2.0f, camDim.y / 2.0f, CAMERA_NEAR_PLANE, CAMERA_FAR_PLANE);
        }

        // Setup Shader Uniforms
        shdr.use();
        shdr.set_vec3("light.amb", lights[0].ambient);
        shdr.set_vec3("light.diff", lights[0].diffuse);
        shdr.set_vec3("light.spec", lights[0].specular);
        shdr.set_vec3("light.pos", lights[0].position);
        shdr.set_vec3("viewPos", renderer.get_camera()->position.x, renderer.get_camera()->position.y, renderer.get_camera()->position.z);
        shdr.set_mat4("view", view);
        shdr.set_mat4("projection", projection);
        shdr.set_texture("tex", &tex);

        // Drawing Shapes and Objects

        // Drawing Objects
        shdr.use();
        set_active_texture(0);
        for (int i = 0; i < actors.size(); i++)
        {
            shdr.set_matrices(transforms[i].get_model_matrix(), view, projection);
            shdr.set_material(actors[i].mat.ambient.color, actors[i].mat.diffuse.color,
                              actors[i].mat.specular.color, actors[i].mat.shininess);
            varray.draw_triangle(36, 0);
        }

        // Drawing Lights
        lightshdr.use();
        lightshdr.set_mat4("view", view);
        lightshdr.set_mat4("projection", projection);
        for (int i = 0; i < lightActors.size(); i++)
        {
            lightshdr.set_matrices(lightActors[i].tr.get_model_matrix(), view, projection);
            lightshdr.set_vec3("col", lightActors[i].mat.diffuse.color);
            varray.draw_triangle(36, 0);
        }

        // Setup UI Windows
        if (!freeRoam)
        {
            // Scene UI
            ImGui::Begin("UI Box");
            // ImGui::ColorEdit3("Object Color", &objectColor.x);
            //  ImGui::SliderFloat("Object Ambience", &objectAmbience, 0.0f, 1.0f);
            //  ImGui::SliderFloat("Object Diffuse", &objectDiffuse, 0.0f, 1.0f);
            //  ImGui::SliderFloat("Object Specular", &objectSpecular, 0.0f, 1.0f);
            //  ImGui::SliderFloat("Object Shininess", &objectShininess, 1.0f, 256.0f);
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
            for (int i = 0; i < sizeof(transforms) / sizeof(Transform); i++)
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

            // Lighting UI
            ImGui::Begin("Lighting UI");
            ImGui::SliderFloat3("Light Position", &lights[0].position.x, -10.0f, 10.0f);
            // ImGui::ColorEdit3("Ambient Colors", &ambientColors[0].x);
            ImGui::ColorEdit3("Background Color", &bkgColor.x);
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

    lightshdr.free_data();
    shdr.free_data();
    varray.free_data();
    renderer.terminate_glfw();
    return 0;
}
