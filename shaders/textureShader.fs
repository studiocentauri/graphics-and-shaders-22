#version 330 core

out vec4 FragColor;
in vec3 color_vertex;
in vec2 texUV;
uniform float Time;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex,texUV);
}
