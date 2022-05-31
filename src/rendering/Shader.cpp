#include "rendering/Shader.h"

Shader::Shader()
{
}

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
    create_shader(vertexPath, fragmentPath);
}

void Shader::create_shader(const char *vertexPath, const char *fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;

    vertexShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);

        std::stringstream vertexShaderStream, fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "Error Shader File Not loaded successfully" << std::endl;
    }

    unsigned int vertex, fragment;
    vertex = compile_shader(vertexCode.c_str(), VERTEX_SHADER);

    if (check_compile_errors(vertex, VERTEX_SHADER))
    {
        return;
    }
    fragment = compile_shader(fragmentCode.c_str(), FRAGMENT_SHADER);

    if (check_compile_errors(fragment, FRAGMENT_SHADER))
    {
        return;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);

    glLinkProgram(id);

    if (check_compile_errors(id, COMBINED_SHADER))
    {
        return;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::compile_shader(const char *code, SHADER_TYPE type)
{
    unsigned int shader;

    if (type == VERTEX_SHADER)
    {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == FRAGMENT_SHADER)
    {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader, 1, &code, NULL);
    glCompileShader(shader);
    return shader;
}

void Shader::use()
{
    glUseProgram(id);
}

void Shader::free_data()
{
    glDeleteProgram(id);
}

bool Shader::check_compile_errors(unsigned int shader, SHADER_TYPE type)
{
    int success;

    char infoLog[1024];

    if (type == COMBINED_SHADER)
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);

        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING FAILED OF TYPE" << std::endl
                      << infoLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILE::LINKING FAILED OF TYPE" << std::endl
                      << infoLog << std::endl;
        }
    }
    return success == 0;
}
