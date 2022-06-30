#ifndef SHADER_H
#define SHADER_H

#include "thirdparty/glad/glad.h"
#include "rendering/Texture.h"
#include "thirdparty/glm/glm.hpp"
#include "thirdparty/glm/gtc/matrix_transform.hpp"
#include "thirdparty/glm/gtc/type_ptr.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// Types of Shaders
enum SHADER_TYPE
{
    VERTEX_SHADER,
    FRAGMENT_SHADER,
    COMBINED_SHADER,
};

// Shader Class
class Shader
{
public:
    unsigned int id;

    Shader();
    Shader(std::string vertexPath, std::string fragmentPath);
    Shader(const char *vertexPath, const char *fragmentPath);
    void create_shader(const char *vertexPath, const char *fragmentPath);
    unsigned int compile_shader(const char *code, SHADER_TYPE type);
    void use();
    void free_data();
    void set_bool(const std::string name, bool value);
    void set_int(const std::string name, int value);
    void set_float(const std::string name, float value);
    void set_vec2(const std::string name, float x, float y);
    void set_vec3(const std::string name, float x, float y, float z);
    void set_mat4(const std::string name, glm::mat4 value);
    void set_texture(const std::string name, Texture *tex);

private:
    bool check_compile_errors(unsigned int shader, SHADER_TYPE type);
};

#endif
