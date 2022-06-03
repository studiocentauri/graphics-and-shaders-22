#version 330 core

out vec4 FragColor;
in vec3 color_vertex;

void main()
{
    FragColor = vec4(color_vertex.xyz, 1.0f);
}
