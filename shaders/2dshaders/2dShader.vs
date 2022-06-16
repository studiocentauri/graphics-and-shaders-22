#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color_vertex;
uniform mat4 model;
void main()
{
    gl_Position = model * vec4(aPos,1.0f);
    color_vertex = aCol;
}