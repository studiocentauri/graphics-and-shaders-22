#include "rendering/Shader.h"

LightSource::LightSource()
{
    ambient = DEFAULT_LIGHT_COLOR;
    diffuse = DEFAULT_LIGHT_COLOR;
    specular = DEFAULT_LIGHT_COLOR;
}

LightSource::LightSource(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_)
{
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
}

PointLight::PointLight()
{
    ambient = DEFAULT_LIGHT_COLOR;
    diffuse = DEFAULT_LIGHT_COLOR;
    specular = DEFAULT_LIGHT_COLOR;
    position = WORLD_ORIGIN;
    type = POINT_LIGHT;
    radius = 2.0f;
    quadratic = 0.2f;
    linear = 0.22f;
    constant = 1.0f;
}

PointLight::PointLight(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, glm::vec3 position_, float radius_, float quadratic_, float linear_, float constant_)
{
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    position = position_;
    type = POINT_LIGHT;
    radius = radius_;
    quadratic = quadratic_;
    linear = linear_;
    constant = constant_;
}

DirectionalLight::DirectionalLight()
{
    ambient = DEFAULT_LIGHT_COLOR;
    diffuse = DEFAULT_LIGHT_COLOR;
    specular = DEFAULT_LIGHT_COLOR;
    type = DIRECTIONAL_LIGHT;
    direction = glm::vec3(-1.0f);
}

DirectionalLight::DirectionalLight(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, glm::vec3 direction_)
{
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    type = DIRECTIONAL_LIGHT;
    direction = direction_;
}

SpotLight::SpotLight()
{
    ambient = DEFAULT_LIGHT_COLOR;
    diffuse = DEFAULT_LIGHT_COLOR;
    specular = DEFAULT_LIGHT_COLOR;
    type = SPOT_LIGHT;
    position = CAMERA_ORIGIN;
    lookAt = glm::normalize(-CAMERA_ORIGIN);
    innerFallOff = 7.5f;
    outerFallOff = 15.0f;
}

SpotLight::SpotLight(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, glm::vec3 position_, glm::vec3 lookAt_, float innerFallOff_, int outerFallOff_)
{
    ambient = ambient_;
    diffuse = diffuse_;
    specular = specular_;
    position = position_;
    type = SPOT_LIGHT;
    lookAt = lookAt_;
    innerFallOff = innerFallOff_;
    outerFallOff = outerFallOff_;
}

Shader::Shader()
{
}

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
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

void Shader::set_vec2(const std::string name, glm::vec2 value)
{
    glUniform2f(glGetUniformLocation(id, name.c_str()), value.x, value.y);
}

void Shader::set_vec3(const std::string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), x, y, z);
}

void Shader::set_vec3(const std::string name, glm::vec3 value)
{
    glUniform3f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z);
}

void Shader::set_vec4(const std::string name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), x, y, z, w);
}

void Shader::set_vec4(const std::string name, glm::vec4 value)
{
    glUniform4f(glGetUniformLocation(id, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::set_mat2(const std::string name, glm::mat2 value)
{
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void Shader::set_mat3(const std::string name, glm::mat3 value)
{
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, &value[0][0]);
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

void Shader::set_matrices(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    set_mat4("model", model);
    set_mat4("view", view);
    set_mat4("projection", projection);
}

void Shader::set_material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
    set_vec3("mat.ambient", ambient);
    set_vec3("mat.diffuse", diffuse);
    set_vec3("mat.specular", specular);
    set_float("mat.shininess", shininess);
}

void Shader::set_point_light(int index, PointLight *light)
{
    set_vec3("pointLights[" + std::to_string(index) + "].amb", light->ambient);
    set_vec3("pointLights[" + std::to_string(index) + "].diff", light->diffuse);
    set_vec3("pointLights[" + std::to_string(index) + "].spec", light->specular);
    set_vec3("pointLights[" + std::to_string(index) + "].pos", light->position);
    set_float("pointLights[" + std::to_string(index) + "].radius", light->radius);
    set_float("pointLights[" + std::to_string(index) + "].constant", light->constant);
    set_float("pointLights[" + std::to_string(index) + "].linear", light->linear);
    set_float("pointLights[" + std::to_string(index) + "].quadratic", light->quadratic);
}

void Shader::set_directional_light(int index, DirectionalLight *light)
{
    set_vec3("dirLights[" + std::to_string(index) + "].amb", light->ambient);
    set_vec3("dirLights[" + std::to_string(index) + "].diff", light->diffuse);
    set_vec3("dirLights[" + std::to_string(index) + "].spec", light->specular);
    set_vec3("dirLights[" + std::to_string(index) + "].direction", light->direction);
}

void Shader::set_spot_light(int index, SpotLight *light)
{
    set_vec3("spotLights[" + std::to_string(index) + "].amb", light->ambient);
    set_vec3("spotLights[" + std::to_string(index) + "].diff", light->diffuse);
    set_vec3("spotLights[" + std::to_string(index) + "].spec", light->specular);
    set_vec3("spotLights[" + std::to_string(index) + "].pos", light->position);
    set_vec3("spotLights[" + std::to_string(index) + "].direction", light->lookAt);
    set_float("spotLights[" + std::to_string(index) + "].innerFalloff", light->innerFallOff);
    set_float("spotLights[" + std::to_string(index) + "].outerFalloff", light->outerFallOff);
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

std::string vShaderNames[] = {"shaders/3dshaders/lighting.vs",
                              "shaders/3dshaders/lighting.vs",
                              "shaders/3dshaders/lighting.vs"};

std::string fShaderNames[] = {"shaders/3dshaders/lightingColor.fs",
                              "shaders/3dshaders/lightingTexture.fs",
                              "shaders/3dshaders/lightingModel.fs"};

Material::Material()
{
    shininess = 64.0f;
    shader = COLOR_SHADER_3D;
}

Material::Material(glm::vec3 ambient_, glm::vec3 diffuse_, glm::vec3 specular_, float shininess_)
{
    ambient = MaterialField(ambient_);
    diffuse = MaterialField(diffuse_);
    specular = MaterialField(specular_);
    shininess = shininess_;
    shader = COLOR_SHADER_3D;
}

Material::Material(unsigned int diffuseTex, unsigned int specularTex, bool hasEmission_, unsigned int emissionTex, float shininess_)
{
    ambient = MaterialField(diffuseTex);
    diffuse = MaterialField(diffuseTex);
    specular = MaterialField(specularTex);
    emission = MaterialField(emissionTex);
    hasEmission = hasEmission_;
    shininess = shininess_;
    shader = TEXTURE_SHADER_3D;
}
