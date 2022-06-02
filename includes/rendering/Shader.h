#ifndef SHADER_H
#define SHADER_H

#include "thirdparty/glad/glad.h"

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

private:
    bool check_compile_errors(unsigned int shader, SHADER_TYPE type);
};

#endif
