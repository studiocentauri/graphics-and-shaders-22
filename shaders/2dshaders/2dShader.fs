#version 460 core

out vec4 FragColor;

in vec3 color_vertex;
in vec3 position;
in vec2 texUV;

uniform float Time;
uniform sampler2D tex;
uniform vec3 col;

void main()
{
    vec3 color = vec3(0.0f,0.0f,0.0f);
    color = col * vec3(texture(tex,texUV));
    FragColor = vec4(color,1.0f);
}
