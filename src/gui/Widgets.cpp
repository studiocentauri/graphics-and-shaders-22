#include "gui/Widgets.h"

void show_main_menu_bar(Renderer *renderer, bool *toRender, bool *showActorUI)
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
        if (ImGui::BeginMenu("View"))
        {
            if (*toRender)
            {
                ImGui::MenuItem("Actor List", NULL, showActorUI);
            }
            else
            {
                ImGui::MenuItem("(No Scene Open)", NULL, false, false);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void show_section_header(const char *title)
{
    ImGui::Separator();
    ImGui::Text(title);
    ImGui::Text("---------------------------");
}

void show_actor_ui(std::vector<RenderActor *> *actors, std::vector<RenderActor> *lightActors, std::vector<LightSource *> *lights, bool *showUI)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    static int selectedIndex = 0;
    if (ImGui::Begin("SCENE ACTOR LIST", showUI, ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close"))
                {
                    *showUI = false;
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        // Left Column
        {
            ImGui::BeginGroup();
            ImGui::BeginChild("Actor List", ImVec2(150, 0), true);
            if (actors->size() > 0 || lightActors->size() > 0)
            {
                for (int i = 0; i < actors->size() + lightActors->size(); i++)
                {
                    RenderActor *rc;
                    if (i < actors->size())
                    {
                        rc = (actors->at(i));
                    }
                    else
                    {
                        rc = &(lightActors->at(i - actors->size()));
                    }
                    char label[64];
                    sprintf(label, rc->name.c_str());
                    if (ImGui::Selectable(label, selectedIndex == i))
                    {
                        selectedIndex = i;
                    }
                }
            }
            ImGui::EndChild();
            ImGui::EndGroup();
        }
        ImGui::SameLine();
        // Right Column
        {
            RenderActor *actor;
            if (actors->size() > 0 || lightActors->size() > 0)
            {
                if (selectedIndex < actors->size())
                {
                    actor = (actors->at(selectedIndex));
                }
                else
                {
                    actor = &(lightActors->at(selectedIndex - actors->size()));
                }
            }
            ImGui::BeginGroup();
            ImGui::BeginChild("Actor Properties", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));
            ImGui::Text(actor->name.c_str());
            show_section_header("DATA");
            ImGui::InputText(":Name", &(actor->name[0]), 30);
            ImGui::Checkbox(":Visibility", &(actor->toRender));
            show_section_header("TRANSFORM");
            ImGui::SliderFloat3(":Position", &(actor->tr.position.x), -10.0f, 10.0f);
            ImGui::SliderFloat3(":Rotation", &(actor->tr.rotation.x), -180.0f, 180.0f);
            ImGui::SliderFloat3(":Scale", &(actor->tr.scale.x), -8.0f, 8.0f);

            if (actor->type == LIGHT_ACTOR)
            {
                if (ImGui::Button("Reset Transform"))
                {
                    actor->tr.reset_transform();
                    actor->tr.scale = glm::vec3(0.2f);
                }
                show_section_header("LIGHT");
                int i = selectedIndex - actors->size();
                switch (lights->at(i)->type)
                {
                case POINT_LIGHT:
                    ImGui::Text("Type:- Point Light");
                    break;
                case DIRECTIONAL_LIGHT:
                    ImGui::Text("Type:- Directional Light");
                    break;
                case SPOT_LIGHT:
                    ImGui::Text("Type:- Spot Light");
                    break;
                default:
                    break;
                }
                ImGui::ColorEdit3(":Light Ambience", &(actor->mat.ambient.color.x));
                ImGui::ColorEdit3(":Light Diffuse", &(actor->mat.diffuse.color.x));
                ImGui::ColorEdit3(":Light Specular", &(actor->mat.specular.color.x));
                switch (lights->at(i)->type)
                {
                case POINT_LIGHT:
                    ImGui::SliderFloat(":Radius", &(((PointLight *)lights->at(i))->radius), 0.0f, 10.0f);
                    ImGui::SliderFloat(":Constant", &(((PointLight *)lights->at(i))->constant), 1.0f, 5.0f);
                    ImGui::SliderFloat(":Linear", &(((PointLight *)lights->at(i))->linear), 0.01f, 3.0f);
                    ImGui::SliderFloat(":Quadratic", &(((PointLight *)lights->at(i))->quadratic), 0.001f, 1.0f);
                    break;
                case DIRECTIONAL_LIGHT:
                    ImGui::SliderFloat3(":Direction", &(((DirectionalLight *)lights->at(i))->direction.x), -1.0f, 1.0f);
                    break;
                case SPOT_LIGHT:
                    ImGui::SliderFloat(":Inner", &(((SpotLight *)lights->at(i))->innerFallOff), 0.01f, (((SpotLight *)lights->at(i))->outerFallOff));
                    ImGui::SliderFloat(":Outer", &(((SpotLight *)lights->at(i))->outerFallOff), (((SpotLight *)lights->at(i))->innerFallOff), 45.0f);
                    break;
                default:
                    break;
                }
            }
            else
            {
                if (ImGui::Button("Reset Transform"))
                {
                    actor->tr.reset_transform();
                }
                show_section_header("MATERIAL");
                int shaderTemplate = int(actor->mat.shader);
                if (ImGui::Combo(":Shader", &(shaderTemplate), &shaderNames[0], LOADED_SHADERS_COUNT))
                {
                    actor->mat.shader = static_cast<SHADER_TEMPLATE>(shaderTemplate);
                }
                int texID = 0;
                switch (actor->mat.shader)
                {
                case COLOR_SHADER_3D:
                    ImGui::ColorEdit3(":Ambient Col", &(actor->mat.ambient.color.x));
                    ImGui::ColorEdit3(":Diffuse Col", &(actor->mat.diffuse.color.x));
                    ImGui::ColorEdit3(":Specular Col", &(actor->mat.specular.color.x));
                    break;
                case TEXTURE_SHADER_3D:
                    texID = int(actor->mat.diffuse.tex);
                    if (ImGui::Combo(":Diffuse", &(texID), &textureNames[0], LOADED_TEXTURES_COUNT))
                    {
                        actor->mat.diffuse.tex = (unsigned int)(texID);
                    }
                    texID = int(actor->mat.specular.tex);
                    if (ImGui::Combo(":Specular", &(texID), &textureNames[0], LOADED_TEXTURES_COUNT))
                    {
                        actor->mat.specular.tex = (unsigned int)(texID);
                    }
                    texID = int(actor->mat.emission.tex);
                    if (ImGui::Combo(":Emission", &(texID), &textureNames[0], LOADED_TEXTURES_COUNT))
                    {
                        actor->mat.emission.tex = (unsigned int)(texID);
                    }
                    break;
                default:
                    break;
                }
                ImGui::SliderFloat(":Shininess", &(actor->mat.shininess), 1.0f, 256.0f);
            }
            ImGui::EndChild();
            ImGui::EndGroup();
        }
    }
    ImGui::End();
}
