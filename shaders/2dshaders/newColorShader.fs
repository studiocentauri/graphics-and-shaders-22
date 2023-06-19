#version 330 core

out vec4 FragColor;
smooth in vec3 color_vertex;
uniform vec3 col;

void main()
{
    FragColor = vec4(color_vertex.xyz, 1.0f);
}
