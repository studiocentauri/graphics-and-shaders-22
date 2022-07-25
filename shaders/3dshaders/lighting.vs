#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aUV;

out vec2 uv;
out vec3 normal;
out vec3 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos,1.0f);
    uv = aUV;
    normal = mat3(transpose(inverse(model)))*aNormal;
    position = (model * vec4(aPos,1.0f)).xyz;
}
