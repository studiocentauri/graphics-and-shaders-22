#version 330 core

out vec4 FragColor;
in vec3 color_vertex;
uniform float Time;

void main()
{
    FragColor = vec4(color_vertex.x, color_vertex.y, color_vertex.z*Time, 1.0f);
}
