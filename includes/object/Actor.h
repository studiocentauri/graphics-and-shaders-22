#ifndef ACTOR_H
#define ACTOR_H

// Custom Headers
#include "object/Transform.h"
#include "rendering/Shader.h"
#include "object/Model.h"

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

// Types of actors
enum ACTOR_TYPE
{
    OBJECT_ACTOR,
    LIGHT_ACTOR,
    MODEL_ACTOR,
};

// RenderActor class for actors which are rendered in a Scene
class RenderActor : public Actor
{
public:
    bool toRender = true; // Whether to render this actor
    Material mat;         // Material for the actor
    ACTOR_TYPE type;      // Defines type of render actor

    // Default RenderActor constructor
    RenderActor(std::string name_ = "New RenderActor");
    // Mat constructor for RenderActor
    RenderActor(Material mat_, ACTOR_TYPE type_ = OBJECT_ACTOR, std::string name_ = "New RenderActor");

private:
};

// ModelActor class for RenderActors with Model component
class ModelActor : public RenderActor
{
public:
    Model *model; // Model Class pointer

    // Default ModelActor constructor
    ModelActor(std::string name_ = "New ModelActor");
    // Path constructor for ModelActor
    ModelActor(std::string path, std::string name_ = "New ModelActor", bool gamma = false);
    // ModelActor destructor
    ~ModelActor();

private:
};

#endif // !ACTOR_H
