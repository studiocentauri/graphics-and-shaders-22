#version 460 core

out vec4 FragColor;

in vec2 UV;

uniform vec3 col;
uniform sampler2D tex;

void main()
{
    vec3 color = vec3(texture(tex,UV));
    color *=col;
    FragColor = vec4(color,1.0f);
}
