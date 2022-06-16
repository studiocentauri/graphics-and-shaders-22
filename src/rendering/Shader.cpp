#include "rendering/Shader.h"

Shader::Shader()
{
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{

    std::cout << vertexPath << fragmentPath;
    create_shader(vertexPath.c_str(), fragmentPath.c_str());
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

    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

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

void Shader::set_bool(const std::string name, bool value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), int(value));
}

void Shader::set_int(const std::string name, int value)
{
    glUniform1i(glGetUniformLocation(id, name.c_str()), int(value));
}
void Shader::set_float(const std::string name, float value)
{
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
}
void Shader::set_vec2(const std::string name, float x, float y)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), x, y);
}
void Shader::set_vec3(const std::string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}
void Shader::set_mat4(const std::string name, glm::mat4 value)
{
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}
void Shader::set_texture(const std::string name, Texture *tex)
{
    set_active_texture(tex->id);
    set_int(name, tex->id);
    tex->bind_texture();
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
