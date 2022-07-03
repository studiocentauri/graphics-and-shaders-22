#include "gui/Widgets.h"

void show_main_menu_bar(Renderer *renderer, bool *toRender)
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open Sample Scene"))
            {
                *toRender = true;
            }
            if (ImGui::MenuItem("Close Scene"))
            {
                *toRender = false;
            }
            if (ImGui::MenuItem("Quit", "Escape"))
            {
                glfwSetWindowShouldClose(renderer->window, true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}
