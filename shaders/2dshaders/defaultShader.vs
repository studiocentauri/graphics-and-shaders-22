#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

out vec3 color_vertex;
uniform float XAxis,YAxis;
void main()
{
    gl_Position = vec4(aPos.x+XAxis, aPos.y+YAxis, aPos.z, 1.0f);
    color_vertex = aCol;
}
