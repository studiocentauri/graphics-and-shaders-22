#version 330 core

out vec4 FragColor;
in vec2 UV;
uniform vec3 col;
uniform sampler2D tex;

void main()
{
    FragColor = texture(tex,UV);
}
