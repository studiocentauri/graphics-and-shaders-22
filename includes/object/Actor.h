#ifndef ACTOR_H
#define ACTOR_H

// Custom Headers
#include "object/Transform.h"
#include "rendering/Shader.h"

// Standard Headers
#include <iostream>

// Actor class for Scene
class Actor
{
public:
    std::string name; // Name of Actor
    Transform tr;     // Transform component for Actor

    // Default Actor Constructor
    Actor(std::string name_ = "New Actor");

private:
};

// RenderActor class for actors which are rendered in a Scene
class RenderActor : public Actor
{
public:
    bool toRender = true; // Whether to render this actor
    Material mat;         // Material for the actor

    // Default RenderActor constructor
    RenderActor(std::string name_ = "New RenderActor");
    // Mat constructor for RenderActor
    RenderActor(Material mat_, std::string name_ = "New RenderActor");
};

#endif // !ACTOR_H
