#include <iostream>
#include "Config.h"
#include "rendering/Renderer.h"

Renderer renderer;

int main()
{
    renderer.initialise_glfw();
    std::cout<<WINDOW_NAME<<std::endl;
    renderer.terminate_glfw();
    return 0;
}

