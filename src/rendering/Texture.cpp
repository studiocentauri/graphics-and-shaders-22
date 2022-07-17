#include "rendering/Texture.h"

Texture::Texture()
{
}

Texture::Texture(std::string path_, bool gamma)
{
    path = path_;
    load_texture_from_path(gamma);
}

void Texture::load_texture_from_path(bool gamma)
{
    generate_texture();

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);

    if (data)
    {
        GLenum format;
        GLenum otherFormat;
        if (nrComponents == 1)
        {
            format = GL_RED;
            otherFormat = format;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
            otherFormat = (gamma) ? (GL_SRGB) : (format);
        }
        else if (nrComponents == 4)
        {
            format = GL_RGBA;
            otherFormat = (gamma) ? (GL_SRGB_ALPHA) : (format);
        }
        bind_texture();

        glTexImage2D(GL_TEXTURE_2D, 0, otherFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
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

void Texture::generate_texture()
{
    glGenTextures(1, &id);
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

std::string texturePaths[] = {
    "resources/textures/bricks.jpg",
    "resources/textures/brickwall.jpg",
    "resources/textures/container.jpg",
    "resources/textures/container.png",
    "resources/textures/container_specular.png",
    "resources/textures/marble.jpg",
    "resources/textures/matrix.jpg",
    "resources/textures/metal.png",
    "resources/textures/wall.jpg",
    "resources/textures/wood.png",
};

std::string texTypes[] = {
    "diffuse",
    "diffuse",
    "diffuse",
    "diffuse",
    "specular",
    "diffuse",
    "diffuse",
    "diffuse",
    "diffuse",
    "diffuse",
};
