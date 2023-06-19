#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

smooth out vec3 color_vertex;
out vec2 texUV;
out vec3 position;
uniform vec2 offset;

void main()
{
    gl_Position = vec4(aPos.x+offset.x, aPos.y+offset.y, aPos.z, 1.0f);
    color_vertex = aCol;
    texUV = aUV;
    position = aPos;
}
