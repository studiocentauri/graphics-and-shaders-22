#version 330 core

out vec4 FragColor;
in vec3 color_vertex;
in vec3 position;
in vec2 texUV;
uniform float Time;
uniform sampler2D tex;
uniform sampler2D tex1;

void main()
{
    vec3 color = vec3(0.0f,0.0f,0.0f);
    if(position.x>=0.0f)
    color = vec3(texture(tex1,texUV));
    else
    color = vec3(texture(tex,texUV));
    FragColor = vec4(color,1.0f);
}
