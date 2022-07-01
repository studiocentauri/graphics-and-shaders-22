#version 330 core

struct Material
{
    float ambience;
    float diffuse;
    float specular;
    float shininess;

};
uniform Material mat;
out vec4 FragColor;
uniform vec3 col;
uniform vec3 ambientLight;
in vec3 normal;
in vec2 uv;
void main()
{
    vec3 objectColor = col;
    vec3 ambient = objectColor * mat.ambience * ambientLight;
    vec3 resultant = ambient;
    FragColor = vec4(resultant.xyz, 1.0f);
}
