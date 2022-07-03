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
