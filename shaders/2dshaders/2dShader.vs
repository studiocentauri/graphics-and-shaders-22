#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec2 aUV;

out vec3 color_vertex;
out vec2 texUV;
out vec3 position;

uniform mat4 model;

void main()
{
    gl_Position = model * vec4(aPos,1.0f);
    color_vertex = aCol;
    texUV = aUV;
    position = aPos;
}
