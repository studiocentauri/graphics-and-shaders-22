#ifndef ACTOR_H
#define ACTOR_H

#include "object/Transform.h"
#include "rendering/Shader.h"
#include <iostream>

class Actor
{
public:
    Transform tr;
    std::string name;

    Actor(std::string name_ = "New Actor");

private:
};

class RenderActor : public Actor
{
public:
    bool toRender = true;
    Material mat;

    RenderActor(std::string name_ = "New RenderActor");
    RenderActor(Material mat_, std::string name_ = "New RenderActor");
};

#endif