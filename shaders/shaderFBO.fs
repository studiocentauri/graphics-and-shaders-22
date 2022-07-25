#version 460 core

out vec4 FragColor;

in vec2 uv;
in vec2 screenPosition;

uniform sampler2D tex;
uniform int cFilter;
uniform float offset;

vec3 get_invert(vec3 col);
vec3 get_grayscale(vec3 col);
vec3 get_kernel(int option);

void main()
{
    vec3 col = vec3(texture(tex, uv));
    if(cFilter==1) // Invert Color
    {
       col=get_invert(col);
    }
    else if(cFilter==2) // Grayscale 
    {
        col=get_grayscale(col);
    }
    else if(cFilter>=3 && cFilter<=6) // Kernel Effects
    {
        col=get_kernel(cFilter);
    }
    FragColor = vec4(col, 1.0f);
}

vec3 get_invert(vec3 col)
{
    col = vec3(1.0f)-col;
    return col;
}

vec3 get_grayscale(vec3 col)
{
    float avg = (0.2126f * col.x + 0.7152f * col.y + 0.0722f * col.z);
    return vec3(avg);
}

vec3 get_kernel(int option)
{
    vec2 offsets[9] = vec2[](
                            vec2(-offset,  offset), // top-left
                            vec2( 0.0f,    offset), // top-center
                            vec2( offset,  offset), // top-right
                            vec2(-offset,  0.0f),   // center-left
                            vec2( 0.0f,    0.0f),   // center-center
                            vec2( offset,  0.0f),   // center-right
                            vec2(-offset, -offset), // bottom-left
                            vec2( 0.0f,   -offset), // bottom-center
                            vec2( offset, -offset)  // bottom-right    
                            );
    
    float kernel[9] = float[](
                            0, 0, 0,
                            0, 1, 0,
                            0, 0, 0);
    if(option==3) // Sharpen
    {
        kernel[0] = -1;
        kernel[1] = -1;
        kernel[2] = -1;
        kernel[3] = -1;
        kernel[4] = 9;
        kernel[5] = -1;
        kernel[6] = -1;
        kernel[7] = -1;
        kernel[8] = -1;
    }
    else if(option==4) // Blur 
    {
        kernel[0] = 1.0 / 16;
        kernel[1] = 2.0 / 16;
        kernel[2] = 1.0 / 16;
        kernel[3] = 2.0 / 16;
        kernel[4] = 4.0 / 16;
        kernel[5] = 2.0 / 16;
        kernel[6] = 1.0 / 16;
        kernel[7] = 2.0 / 16;
        kernel[8] = 1.0 / 16;
    }
    else if(option==5) // Edge 
    {
        kernel[0] = 1;
      kernel[1] = 1;
      kernel[2] = 1;
      kernel[3] = 1;
      kernel[4] = -8;
      kernel[5] = 1;
      kernel[6] = 1;
      kernel[7] = 1;
      kernel[8] = 1;
    }
    else if(option==6) // Emboss 
    {
        kernel[0] = -2;
        kernel[1] = -1;
        kernel[2] = 0;
        kernel[3] = -1;
        kernel[4] = 1;
        kernel[5] = 1;
        kernel[6] = 0;
        kernel[7] = 1;
        kernel[8] = 2;
    }

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(tex, uv.st + offsets[i]));
    }
    
    vec3 col=vec3(0.0f);
    for(int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }

    return col;
}
