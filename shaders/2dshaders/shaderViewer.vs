#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

out vec2 texUV;
out vec3 position;
out vec2 screenPosition;

void main()
{
    gl_Position = vec4(aPos,1.0f);
    screenPosition = gl_Position.xy;
    texUV = aUV;
    position = aPos;
}
