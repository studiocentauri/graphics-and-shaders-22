#include "Config.h"
#include "rendering/Renderer.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"
#include "utility/FileSystem.h"
#include "thirdparty/imgui/imgui.h"
#include "thirdparty/imgui/imgui_impl_glfw.h"
#include "thirdparty/imgui/imgui_impl_opengl3.h"

#include <iostream>

Renderer renderer;

// float vertices[] = {
//     -0.5f, -0.5f, 0.0f,
//     0.5f, -0.5f, 0.0f,
//     0.0f, 0.5f, 0.0f};

float vertices[] = {
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.5f,

    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    0.75f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    0.75f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,

};

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
    //varray.bind_vbo(3, 8 * sizeof(float), vertices);
    // varray.bind_ebo(6, indices);
    //varray.set_attribute_array(0, 3, 8 * sizeof(float));
    //varray.set_attribute_array(1, 3, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    //varray.set_attribute_array(2, 2, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    varray.unbind_vbo();
    varray.unbind_vao();

    // Setup Shaders and Textures
    Shader shdr(FileSystem::get_path("shaders/2dshaders/defaultShader.vs").c_str(), FileSystem::get_path("shaders/2dshaders/colorShader.fs").c_str());
    Shader shdr2(FileSystem::get_path("shaders/2dshaders/textureShader.vs").c_str(), FileSystem::get_path("shaders/2dshaders/textureShader.fs").c_str());
    Shader shdr3(FileSystem::get_path("shaders/2dshaders/newVertexShader.vs").c_str(), FileSystem::get_path("shaders/2dshaders/newColorShader.fs").c_str());
    
    Shader shdr4(FileSystem::get_path("shaders/2dshaders/defaultShader.vs").c_str(), FileSystem::get_path("shaders/2dshaders/colorShader.fs").c_str());


    Texture tex(FileSystem::get_path("resources/textures/iitk_logo.png"));
    Texture tex1(FileSystem::get_path("resources/textures/logo4.png"));
    Texture tex2(FileSystem::get_path("resources/textures/council_logo.png"));

    // Setup Data
    float totalTime = 0;
    float xAxis = 0, yAxis = 0;
    float translationSpeed = 1.0f;
    ImVec4 objectColor(0.8f, 0.5f, 0.2f, 1.0f);
    ImVec4 bkgColor(0.2f, 0.3f, 0.2f, 1.0f);
    const char *drawOptions[3] = {"Point", "Line", "Fill"};
    const char *texSelect[3] = { "Texture1", "Texture2", "Texture3"};
    Texture texarr[] = {tex, tex1, tex2}; // Array of textures?

    int drawOption = 2;
    int texSelected = 0;
    bool isRotating = false;
    bool check[4]={false, false, false, false};

    float timePeriod = 5.0f;

    // Start Render Loop
    renderer.start_timer();
    float timer = 1;
    bool vSync = false;
    int FPS = 30;
    while (!renderer.close_window())
    {
        // Frame Start
        renderer.new_frame();

        totalTime += renderer.deltaTime;
        FPS = (int) (1.0f / renderer.deltaTime);

        totalTime = (totalTime > timePeriod) ? (totalTime - timePeriod) : totalTime;
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

        // for rotating triangle
        if (renderer.check_key(GLFW_KEY_R))
        {
            isRotating = !isRotating;
        }
        if (isRotating == 0) std::cout << "NOT Rotating\n";
        else std::cout << "RRRRRRRRRRRRRRRRRRR\n";

        //get centroid 
        int n_Vertices = (sizeof(vertices) / sizeof(float) )/8;
        float gX = 0, gY = 0;

        std::cout << "there are vertices" << n_Vertices << "\n";
        int i = 0;
        for (int i = 0; i < n_Vertices * 8; i+=8);
        {
            gX += vertices[i];
            gY += vertices[i + 1];
        }
        gX /= n_Vertices;
        gY /= n_Vertices;
        gX = 0;
        gY = 0;
        float theta = 0.005f;
        if (isRotating == 1)
        {
            int i = 0;
            for (i = 0; i < n_Vertices * 8; i += 8)
            {
                std::cout << i << " " << " OG VERTICES : " << vertices[i] << " " << vertices[i + 1] << " \n";

                float new_x, new_y, new_xx, new_yy;
                new_x = (vertices[i]-gX) * cos(theta) - (vertices[i + 1]-gY) * sin(theta) + gX;
                new_y = (vertices[i]-gX) * sin(theta) + (vertices[i + 1]-gY) * cos(theta) + gY;
                /* new_x = vertices[i] - gX;
                new_y = vertices[i+1] - gY;
                new_xx = new_x * cos(theta) - new_y * sin(theta);
                new_yy = new_x * sin(theta) + new_y * cos(theta);
                new_x = new_xx + gX;
                new_y = new_yy + gY; */
                vertices[i] = new_x;
                vertices[i + 1] = new_y;

                std::cout << i << " " << " NUUUUU VERTICES : " << vertices[i] << " " << vertices[i + 1] << " \n";
            }
        }

        varray.generate_buffers();
        varray.bind_vao();

        shdr4.use();
        //shdr2.set_texture("tex", &tex);


        if (check[0] == 1 && check[1] == 0) {
            shdr2.use();
            shdr2.set_texture("tex1", &texarr[texSelected]);
            shdr2.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
            //shdr2.set_float("Time", totalTime);
            shdr2.set_vec2("offset", xAxis, yAxis);
            varray.bind_vbo(3, 8 * sizeof(float), vertices);
            varray.set_attribute_array(0, 3, 8 * sizeof(float));
            varray.set_attribute_array(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            varray.set_attribute_array(2, 3, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        }
        else if (check[1] == 1 && check[0] == 0)
        {
            shdr2.use();
            shdr2.set_texture("tex1", &texarr[texSelected]);
            shdr2.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
            //shdr2.set_float("Time", totalTime);
            shdr2.set_vec2("offset", xAxis, yAxis);
            varray.bind_vbo(4, 8 * sizeof(float), vertices + 8 * 3);
            varray.set_attribute_array(0, 4, 8 * sizeof(float));
            varray.set_attribute_array(1, 4, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            varray.set_attribute_array(2, 4, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        }
        //fixing rectangle + both checked also left
        
        else if (check[0] == 1 && check[1] == 1)
        {
            shdr2.use();
            shdr2.use();
            shdr2.set_texture("tex1", &texarr[texSelected]);
            shdr2.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
            //shdr2.set_float("Time", totalTime);
            shdr2.set_vec2("offset", xAxis, yAxis);
            varray.bind_vbo(3, 8 * sizeof(float), vertices);
            varray.set_attribute_array(0, 3, 8 * sizeof(float));
            varray.set_attribute_array(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            varray.set_attribute_array(2, 3, 8 * sizeof(float), (void*)(6 * sizeof(float)));
            
        }
        else
        {
            if (totalTime < timePeriod / 3.)
            {
                vertices[3] = vertices[12] = vertices[21] = 1.0f - (totalTime) * (3 / timePeriod);
                vertices[4] = vertices[13] = vertices[19] = 0.0f;
                vertices[5] = vertices[11] = vertices[20] = totalTime * 3/timePeriod;
            }
            else if (totalTime < (2 * timePeriod / 3.))
            {
                vertices[5] = vertices[11] = vertices[20] = 1.0f - (totalTime) * (3 / timePeriod) + 1.0f;
                vertices[3] = vertices[12] = vertices[21] = 0.0f;
                vertices[4] = vertices[13] = vertices[19] = (totalTime) * 3 / timePeriod - 1.0f;
            }
            else if (totalTime < timePeriod)
            {
                vertices[4] = vertices[13] = vertices[19] = 1.0f - (totalTime) * (3 / timePeriod) + 2.0f;
                vertices[5] = vertices[11] = vertices[20] = 0.0f;
                vertices[3] = vertices[12] = vertices[21] = totalTime * 3 / timePeriod - 2.0f;
            }

            shdr4.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);

            shdr4.use();
            varray.bind_vbo(3, 8 * sizeof(float), vertices);
            varray.set_attribute_array(0, 3, 8 * sizeof(float));
            varray.set_attribute_array(1, 3, 8 * sizeof(float), (void*)(3 * sizeof(float)));
            varray.set_attribute_array(2, 3, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        }
        //varray.bind_ebo(6, indices);
        varray.unbind_vbo();
        varray.unbind_vao();

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

        // Setup Shader Uniforms
        /* shdr.use();
        shdr.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);
        shdr.set_float("Time", totalTime);
        shdr.set_vec2("offset", xAxis, yAxis); */

        // Drawing Shapes and Objects

        if (check[0] == 1 && check[1] == 0) {
            varray.draw_triangle(3, 0);
        }
        else if (check[1] == 1 && check[0] == 0)
        {
            varray.draw_triangle(3, 0);
            varray.draw_triangle(3, 1);
        }
        else if (check[0] == 1 && check[1] == 1)
        {
           varray.draw_triangle(3, 0);

           shdr2.use();

           varray.bind_vbo(4, 8 * sizeof(float), vertices + 8 * 3);
           varray.set_attribute_array(0, 4, 8 * sizeof(float));
           varray.set_attribute_array(1, 4, 8 * sizeof(float), (void*)(3 * sizeof(float)));
           varray.set_attribute_array(2, 4, 8 * sizeof(float), (void*)(6 * sizeof(float)));
           varray.draw_triangle(3, 0);
           varray.draw_triangle(3, 1);
           // varray.draw_triangle(3, 1);

        }
        else
        {
            if (check[3] == 1) shdr3.use();
            else {
                shdr4.use();
            }
            //shdr.set_vec3("col", objectColor.x, objectColor.y, objectColor.z);

            shdr3.set_float("Time", totalTime);
            shdr3.set_vec2("offset", xAxis, yAxis);
            varray.draw_triangle(3, 0);

        }
        //set_active_texture(0);
        //varray.draw_triangle(3, 0);
        // varray.draw_indices(6);
       
        // Setup UI Windows
        ImGui::Begin("UI Box");
        ImGui::ColorEdit3("Object Color", &objectColor.x);
        ImGui::ColorEdit3("Background Color", &bkgColor.x);
        ImGui::SliderFloat("SliderX", &xAxis, -0.5f, 0.5f);
        ImGui::SliderFloat("SliderY", &yAxis, -0.5f, 0.5f);
        ImGui::Combo("RenderMode", &drawOption, &drawOptions[0], 3);
        ImGui::End();

        ImGui::Begin("New controls");
        ImGui::Checkbox("Draw Color Cycle", &check[3]);
        ImGui::Checkbox("Draw Triangle", &check[0]);
        ImGui::Checkbox("Draw Rectangle", &check[1]);
        ImGui::Checkbox("Show FPS", &check[2]);
        ImGui::Checkbox("Rotating?", &isRotating);
        ImGui::Checkbox("vSync?", &vSync);


        if (check[2])
        {
            ImGui::Text("%d FPS", FPS);
        }
        ImGui::Combo("Select texture", &texSelected, &texSelect[0], 3);
        //ImGui::Text("Texture is %d", texSelected);
        ImGui::End();

        // Draw UI
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // End of Frame
        renderer.swap_buffers(vSync);
    }

    // Free Data and stop processes
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    shdr.free_data();
    varray.free_data();
    renderer.terminate_glfw();
    return 0;
}
