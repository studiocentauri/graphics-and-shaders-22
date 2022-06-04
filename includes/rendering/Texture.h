#ifndef TEXTURE_H
#define TEXTURE_H

#include "thirdparty/glad/glad.h"
#include "thirdparty/GLFW/glfw3.h"
#include "thirdparty/stb_image.h"
#include <iostream>

class Texture
{
    public:
    unsigned int id;
    std::string path;

    Texture();
    Texture(std::string _path);
    void load_texture_from_path();
    void generate_texture();
    void bind_texture();
    void unbind_texture();

    private:
};

void set_active_texture(int index);

#endif