// Third-party Headers
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
#include "gui/GUI.h"
#include "gui/Widgets.h"

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
bool renderScene = true;
bool showActorUI = true;
std::vector<Shader> templateShaders;
std::vector<Texture> textures;

// Sets the template shaders via path
void load_template_shaders();
void load_template_textures();

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
    load_template_shaders();
    load_template_textures();
    // Setting up imgui
    GUI gui(renderer.window, renderer.major, renderer.minor);

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
    Shader lightshdr(FileSystem::get_path("shaders/3dshaders/colorShader.vs").c_str(), FileSystem::get_path("shaders/3dshaders/colorShader.fs").c_str());
    // Setup Data
    float totalTime = 0;
    ImVec4 bkgColor(55.0f / 255.0f, 100.0f / 255.0f, 110.0f / 255.0f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    int drawOption = 2;
    bool isPerspective = true;
    bool freeRoam = false;
    bool showFrameRate = false;
    bool lockFrameRate = true;

    Transform transforms[] = {Transform(glm::vec3(0.0f, 0.0f, -5.0f)),
                              Transform(glm::vec3(1.5f, 1.0f, -4.0f)),
                              Transform(glm::vec3(-1.0f, -1.0f, -3.0f)),
                              Transform(glm::vec3(-2.0f, 2.0f, -2.0f)),
                              Transform(glm::vec3(2.0f, -2.0f, -1.0f))};
    for (int i = 0; i < 5; i++)
    {
        RenderActor rc("Cube " + std::to_string(i + 1));
        Material mat(3, 4, true, 5, 64.0f);
        rc.mat = mat;
        rc.tr = transforms[i];
        rc.type = OBJECT_ACTOR;
        actors.push_back(rc);
    }

    Transform lightstr[] = {Transform(glm::vec3(0.7f, 1.0f, 1.0f), glm::vec3(0.0f), glm::vec3(0.2f))};
    for (int i = 0; i < 1; i++)
    {
        RenderActor rc("Light " + std::to_string(i + 1));
        Material mat(glm::vec3(0.2f), glm::vec3(0.7f), glm::vec3(0.4f));
        rc.mat = mat;
        rc.tr = lightstr[i];
        rc.type = LIGHT_ACTOR;
        lightActors.push_back(rc);
    }
    for (int i = 0; i < lightActors.size(); i++)
    {
        LightSource ls;
        ls.position = lightActors[i].tr.position;
        ls.ambient = lightActors[i].mat.ambient.color;
        ls.diffuse = lightActors[i].mat.diffuse.color;
        ls.specular = lightActors[i].mat.specular.color;
        lights.push_back(ls);
    }

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
        if (renderScene)
        {
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
            for (int i = 0; i < lightActors.size(); i++)
            {
                lights[i].position = lightActors[i].tr.position;
                lights[i].ambient = lightActors[i].mat.ambient.color;
                lights[i].diffuse = lightActors[i].mat.diffuse.color;
                lights[i].specular = lightActors[i].mat.specular.color;
            }

            // Setup Shader Uniforms
            set_active_texture(0);
            for (int i = 0; i < actors.size(); i++)
            {
                if (actors[i].toRender)
                {
                    Shader *shdr = &(templateShaders[int(actors[i].mat.shader)]);
                    shdr->use();
                    switch (actors[i].mat.shader)
                    {
                    case COLOR_SHADER_3D:
                        shdr->set_vec3("light.amb", lights[0].ambient);
                        shdr->set_vec3("light.diff", lights[0].diffuse);
                        shdr->set_vec3("light.spec", lights[0].specular);
                        shdr->set_vec3("light.pos", lights[0].position);
                        shdr->set_vec3("viewPos", renderer.get_camera()->position);
                        shdr->set_matrices(actors[i].tr.get_model_matrix(), view, projection);
                        shdr->set_material(actors[i].mat.ambient.color, actors[i].mat.diffuse.color,
                                           actors[i].mat.specular.color, actors[i].mat.shininess);
                        break;
                    case TEXTURE_SHADER_3D:
                        shdr->set_vec3("light.amb", lights[0].ambient);
                        shdr->set_vec3("light.diff", lights[0].diffuse);
                        shdr->set_vec3("light.spec", lights[0].specular);
                        shdr->set_vec3("light.pos", lights[0].position);
                        shdr->set_vec3("viewPos", renderer.get_camera()->position);
                        shdr->set_texture("mat.diffuse", &(textures[actors[i].mat.diffuse.tex]));
                        shdr->set_texture("mat.specular", &(textures[actors[i].mat.specular.tex]));
                        shdr->set_texture("mat.emission", &(textures[actors[i].mat.emission.tex]));
                        shdr->set_float("mat.shininess", actors[i].mat.shininess);
                        shdr->set_matrices(actors[i].tr.get_model_matrix(), view, projection);
                        break;
                    default:
                        break;
                    }
                    // Drawing Objects
                    varray.draw_triangle(36, 0);
                }
            }

            // Drawing Lights
            lightshdr.use();
            for (int i = 0; i < lightActors.size(); i++)
            {
                if (lightActors[i].toRender)
                {
                    lightshdr.set_matrices(lightActors[i].tr.get_model_matrix(), view, projection);
                    lightshdr.set_vec3("col", lightActors[i].mat.ambient.color);
                    varray.draw_triangle(36, 0);
                }
            }

            // Setup UI Windows
            if (!freeRoam)
            {
                if (showActorUI)
                {
                    show_actor_ui(&actors, &lightActors, &showActorUI);
                }
                // Scene UI
                ImGui::Begin("Scene UI");
                ImGui::ColorEdit3("Background Color", &bkgColor.x);
                ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
                ImGui::Checkbox("IsPerspective", &isPerspective);
                ImGui::Checkbox("VSync", &lockFrameRate);
                ImGui::Checkbox("Show FPS", &showFrameRate);
                if (showFrameRate)
                {
                    ImGui::Text("%d FPS", (int)(1 / renderer.deltaTime));
                }
                ImGui::End();
            }
        }
        else
        {
            // Clear Previous Frame
            glClearColor(DEFAULT_BACKGROUND_COLOR.x, DEFAULT_BACKGROUND_COLOR.y, DEFAULT_BACKGROUND_COLOR.z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        show_main_menu_bar(&renderer, &renderScene, &showActorUI);

        // Draw UI
        gui.render_gui();

        // End of Frame
        renderer.swap_buffers(lockFrameRate);
    }

    // Free Date and stop processes
    gui.terminate_gui();

    lightshdr.free_data();
    varray.free_data();
    renderer.terminate_glfw();
    return 0;
}

void load_template_shaders()
{
    for (int i = 0; i < LOADED_SHADERS_COUNT; i++)
    {
        Shader shdr(FileSystem::get_path(vShaderNames[i]), FileSystem::get_path(fShaderNames[i]));
        templateShaders.push_back(shdr);
    }
}

void load_template_textures()
{
    for (int i = 0; i < LOADED_TEXTURES_COUNT; i++)
    {
        Texture tex(FileSystem::get_path(texturePaths[i]));
        textures.push_back(tex);
    }
}