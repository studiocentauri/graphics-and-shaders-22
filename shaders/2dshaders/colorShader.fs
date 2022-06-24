#version 330 core

out vec4 FragColor;
in vec3 color_vertex;
uniform vec3 col;

void main()
{
    FragColor = vec4(col.xyz, 1.0f);
}