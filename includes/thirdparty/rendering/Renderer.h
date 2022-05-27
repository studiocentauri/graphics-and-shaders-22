#ifndef RENDERER_H
#define RENDERER_H
#include "Config.h"
#include "thirdparty/glad/glad.h"
#include "thirdparty/GLFW/glfw3.h"

//Rendering class
class Renderer
{
    private:

    public:
    int major;
    int minor;
    int width;
    int height;
    Renderer(int major_=OPENGL_MAJOR_VERSION, int minor_=OPENGL_MINOR_VERSION, int width_=WINDOW_WIDTH, int height_=WINDOW_HEIGHT);
    void initialise_glfw();
    void terminate_glfw();
};

#endif