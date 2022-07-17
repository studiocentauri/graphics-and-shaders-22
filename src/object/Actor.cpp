#include "object/Actor.h"

Actor::Actor(std::string name_)
{
    name = name_;
}

RenderActor::RenderActor(std::string name_)
{
    name = name_;
    type = OBJECT_ACTOR;
}

RenderActor::RenderActor(Material mat_, ACTOR_TYPE type_, std::string name_)
{
    mat = mat_;
    type = type_;
    name = name_;
}

ModelActor::ModelActor(std::string name_)
{
    type = MODEL_ACTOR;
    name = name_;
}

ModelActor::ModelActor(std::string path, std::string name_, bool gamma)
{
    model = new Model(path, gamma);
    type = MODEL_ACTOR;
    name = name_;
}

ModelActor::~ModelActor()
{
    delete model;
}
