#version 460 core

out vec4 FragColor;

uniform vec3 col;

void main()
{
    FragColor = vec4(col.xyz, 1.0f);
}
