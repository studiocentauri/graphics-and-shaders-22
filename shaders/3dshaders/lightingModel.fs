#version 460 core

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;
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
uniform bool enablePointLight;

struct DirectionalLight {
    vec3 amb;
    vec3 diff;
    vec3 spec;

    vec3 direction;
};
#define MAX_DIRECTIONAL_LIGHTS 3
uniform DirectionalLight dirLights[MAX_DIRECTIONAL_LIGHTS];
uniform int dirLightCount;
uniform bool enableDirLight;

struct SpotLight {
    vec3 amb;
    vec3 diff;
    vec3 spec;

    vec3 direction;
    vec3 pos;

    float innerFalloff;
    float outerFalloff;
};
#define MAX_SPOT_LIGHTS 1
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];
uniform int spotLightCount;
uniform bool enableSpotLight;

out vec4 FragColor;

in vec3 normal;
in vec2 uv;
in vec3 position;

uniform vec3 viewPos;
uniform bool enableBlinnPhong;
uniform bool enableGamma;
float gamma=2.2f;

vec3 get_ambient(vec3 amb);
vec3 get_diffuse(vec3 diff,vec3 lightDir); // lightDir is point to light Direction
vec3 get_specular(vec3 spec,vec3 lightDir, vec3 viewDirection); // lightDir is point to light Direction
vec3 calculate_for_point_light(PointLight light, vec3 viewDirection);
vec3 calculate_for_directional_light(DirectionalLight light, vec3 viewDirection);
vec3 calculate_for_spot_light(SpotLight light, vec3 viewDirection);

void main() 
{
    vec3 resultant = vec3(0.0f);
    vec3 viewDirection = normalize(viewPos - position);
   
    if(enablePointLight)
    {
        for(int i=0; i < min(MAX_POINT_LIGHTS, pointLightCount); i++)
        {
            resultant += calculate_for_point_light(pointLights[i], viewDirection);
        }
    }
    
    if(enableDirLight)
    {
         for(int i=0; i < min(MAX_DIRECTIONAL_LIGHTS, dirLightCount); i++)
        {
            resultant += calculate_for_directional_light(dirLights[i], viewDirection);
        }
    }

    if(enableSpotLight)
    {
         for(int i=0; i < min(MAX_SPOT_LIGHTS, spotLightCount); i++)
        {
            resultant += calculate_for_spot_light(spotLights[i], viewDirection);
        }
    }
    
    if(enableGamma)
    {
        resultant=pow(resultant,vec3(1.0f/gamma));
    }
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
        if(enableGamma)
        {
            att = 1.0f / (light.constant+light.quadratic*distance*distance);
        }
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

    vec3 diffuse = get_diffuse(light.diff, -light.direction);

    vec3 specular = get_specular(light.spec, -light.direction, viewDirection);
    
    return (ambient+diffuse+specular);
}

vec3 calculate_for_spot_light(SpotLight light, vec3 viewDirection)
{
    vec3 lightDir=normalize(light.pos-position);

    float theta=(dot(normalize(-light.direction),lightDir));
    float epsilon=cos((3.14f/180.0f)*light.innerFalloff)-cos((3.14f/180.0f)*light.outerFalloff);
    
    float intensity=clamp(((theta-cos((3.14f/180.0f)*light.outerFalloff))/epsilon),0.0f,1.0f);
    
    vec3 ambient = get_ambient(light.amb);

    vec3 diffuse = get_diffuse(light.diff, lightDir);

    vec3 specular = get_specular(light.spec, lightDir, viewDirection);
    
    return (ambient + (diffuse*intensity) + (specular*intensity));
}

vec3 get_ambient(vec3 amb)
{
    return (vec3(texture(mat.diffuse1,uv)) * amb);
}

vec3 get_diffuse(vec3 diff, vec3 lightDir)
{
    float diffuseFactor = max(0, dot(normalize(normal), lightDir));
    return (vec3(texture(mat.diffuse1,uv)) * diffuseFactor * diff);
}

vec3 get_specular(vec3 spec, vec3 lightDir, vec3 viewDirection)
{
    float specularFactor=0.0f;
    if(enableBlinnPhong)
    {
        vec3 halfDir=normalize(viewDirection+lightDir);
        specularFactor = pow(max(0, dot(normal, halfDir)), mat.shininess*2.0f);
    }
    else
    {
        vec3 reflected = normalize(reflect(-lightDir, normalize(normal)));
        specularFactor = pow(max(0, dot(reflected, viewDirection)), mat.shininess);
    }
    return (vec3(texture(mat.specular1,uv)) * specularFactor * spec);
}
