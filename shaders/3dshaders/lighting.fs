#version 330 core

out vec4 FragColor;
uniform vec3 col;
uniform vec3 ambience;
in vec3 normal;
in vec2 uv;
void main()
{
    vec3 objectColor = col;
    vec3 ambient = objectColor * ambience;
    vec3 resultant = ambient;
    FragColor = vec4(resultant.xyz, 1.0f);
}
