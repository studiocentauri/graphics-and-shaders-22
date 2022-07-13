#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material mat;

struct PointLight {
    vec3 amb;
    vec3 diff;
    vec3 spec;

    vec3 pos;
    float radius;
    float constant;
    float linear;
    float quadratic;
};
#define MAX_POINT_LIGHTS 5
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform int pointLightCount;

struct DirectionalLight {
    vec3 amb;
    vec3 diff;
    vec3 spec;

    vec3 direction;
};
#define MAX_DIRECTIONAL_LIGHTS 3
uniform DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS];
uniform int dirLightCount;

struct SpotLight {
    vec3 amb;
    vec3 diff;
    vec3 spec;

    vec3 direction;
    vec3 pos;

    float innerCutoff;
    float outerCutoff;
};
#define MAX_SPOT_LIGHTS 1
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int spotLightCount;

out vec4 FragColor;

in vec3 normal;
in vec2 uv;
in vec3 position;

uniform vec3 viewPos;
uniform sampler2D tex;

vec3 get_ambient(vec3 amb);
vec3 get_diffuse(vec3 diff,vec3 dir);
vec3 get_specular(vec3 spec,vec3 dir, vec3 viewDirection);
vec3 calculate_for_point_light(PointLight light, vec3 viewDirection);
vec3 calculate_for_directional_light(DirectionalLight light, vec3 viewDirection);

void main() 
{
    vec3 resultant = vec3(0.0f);
    vec3 viewDirection = normalize(viewPos - position);
    
    for(int i=0; i < min(MAX_POINT_LIGHTS, pointLightCount); i++)
    {
        resultant += calculate_for_point_light(pointLights[i], viewDirection);
    }

    for(int i=0; i < min(MAX_DIRECTIONAL_LIGHTS, dirLightCount); i++)
    {
        resultant += calculate_for_directional_light(dirLights[i], viewDirection);
    }

    vec3 emission = vec3(0.0f);
    if(texture(mat.specular,uv).x<0.1f)
    {
        emission = vec3(texture(mat.emission,uv));
    }
    resultant += emission;
    FragColor = vec4(resultant.xyz, 1.0f);
}

vec3 calculate_for_point_light(PointLight light, vec3 viewDirection)
{
    float distance = length(light.pos-position);
    float att = 1.0f;
    if(distance > light.radius)
    {
        distance -= light.radius;
        att = 1.0f / (light.constant+light.linear*distance+light.quadratic*distance*distance);
    }

    vec3 ambient = get_ambient(light.amb);

    vec3 lightDir = normalize(light.pos - position);
    vec3 diffuse = get_diffuse(light.diff, lightDir);

    vec3 specular = get_specular(light.spec, lightDir, viewDirection);

    return att*(ambient+diffuse+specular);
}
vec3 calculate_for_directional_light(DirectionalLight light, vec3 viewDirection)
{
    vec3 ambient = get_ambient(light.amb);

    vec3 diffuse = get_diffuse(light.diff, light.direction);

    vec3 specular = get_specular(light.spec, light.direction, viewDirection);
    return (ambient+diffuse+specular);
}

vec3 get_ambient(vec3 amb)
{
    return (vec3(texture(mat.diffuse,uv)) * amb);
}

vec3 get_diffuse(vec3 diff, vec3 dir)
{
    float diffuseFactor = max(0, dot(normalize(normal), dir));
    return (vec3(texture(mat.diffuse,uv)) * diffuseFactor * diff);
}

vec3 get_specular(vec3 spec, vec3 dir, vec3 viewDirection)
{
    vec3 reflected = normalize(reflect(-dir, normalize(normal)));
    float specularFactor = pow(max(0, dot(reflected, viewDirection)), mat.shininess);
    return (vec3(texture(mat.specular,uv)) * specularFactor * spec);
}
