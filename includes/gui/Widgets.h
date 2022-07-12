#ifndef WIDGETS_H
#define WIDGETS_H

// Custom Headers
#include "gui/GUI.h"
#include "rendering/Renderer.h"
#include "object/Actor.h"
#include "rendering/Shader.h"
#include "rendering/Texture.h"

// Standard Headers
#include <iostream>
#include <vector>

// Shows the main menu bar on top on screen
void show_main_menu_bar(Renderer *renderer, bool *toRender, bool *showActorUI);
// Shows a section in Actor UI
void show_section_header(const char *title);
// Shows Actor UI window
void show_actor_ui(std::vector<RenderActor *> *actors, std::vector<RenderActor> *lightActors, std::vector<LightSource *> *lights, bool *showUI);

#endif // !WIDGETS_H
