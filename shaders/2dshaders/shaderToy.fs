#version 460 core

out vec4 FragColor;

in vec3 position;
in vec2 texUV;
in vec2 screenPosition;

uniform float iTime;
uniform float iTimeDelta;
uniform vec2 iResolution;
uniform sampler2D iChannel0;
uniform sampler2D iChannel1;

vec4 mainImage(vec2 fragCoord);

void main()
{
    vec2 pixPos;
    pixPos = (screenPosition + vec2(1.0f, 1.0f))/2.0f;
    pixPos *= iResolution;
    FragColor = mainImage(pixPos);
}

vec4 mainImage(vec2 fragCoord )
{
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = fragCoord/iResolution.xy;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5*cos(iTime+uv.xyx+vec3(0,2,4));

    // Output to screen
    vec4 fragColor = vec4(col,1.0);
    return fragColor;
}
