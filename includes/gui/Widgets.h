#ifndef WIDGETS_H
#define WIDGETS_H

#include "gui/GUI.h"
#include "rendering/Renderer.h"
#include "object/Actor.h"

#include <iostream>
#include <vector>

void show_main_menu_bar(Renderer *renderer, bool *toRender, bool *showActorUI);
void show_section_header(const char *title);
void show_actor_ui(std::vector<RenderActor> *actors, std::vector<RenderActor> *lightActors, bool *showUI);

#endif // !WIDGETS_H
