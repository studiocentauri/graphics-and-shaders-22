#include <iostream>
#include "Config.h"
#include "GLFW/glfw3.h"

int main()
{
    glfwInit();
    std::cout<<WINDOW_NAME<<std::endl;
    glfwTerminate();
    return 0;
}

