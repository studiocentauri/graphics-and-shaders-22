#include "rendering/Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string _path) : path(_path)
{
    load_texture_from_path();
}

void Texture::generate_texture()
{
    glGenTextures(1, &id);
}

void Texture::load_texture_from_path()
{
    generate_texture();
    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;

        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
        }
        bind_texture();

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        std::cout << "Failed to load Texture" << std::endl;
    }

    stbi_image_free(data);
}

void Texture::bind_texture()
{
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind_texture()
{
    glActiveTexture(GL_TEXTURE0);
}

void set_active_texture(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
}
