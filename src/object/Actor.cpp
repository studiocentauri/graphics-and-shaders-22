#include "object/Actor.h"

Actor::Actor(std::string name_)
{
    name = name_;
}

RenderActor::RenderActor(std::string name_)
{
    name = name_;
}

RenderActor::RenderActor(Material mat_, std::string name_)
{
    mat = mat_;
    name = name_;
}
