#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;

};
uniform Material mat;

struct Light {
    vec3 amb;
    vec3 diff;
    vec3 spec;
    vec3 pos;
};
uniform Light light;

out vec4 FragColor;
in vec3 normal;
in vec2 uv;
in vec3 position;

uniform vec3 viewPos;
uniform sampler2D tex;

void main() {
    vec3 ambient = vec3(texture(mat.diffuse,uv)) * light.amb;

    vec3 norm = normalize(normal);
    vec3 incident = normalize(light.pos - position);

    float diffuseFactor = max(0, dot(norm, incident));
    vec3 diffuse = vec3(texture(mat.diffuse,uv)) * diffuseFactor * light.diff;

    vec3 reflected = normalize(reflect(-incident, norm));
    vec3 viewDirection = normalize(viewPos - position);

    float specularFactor = pow(max(0, dot(reflected, viewDirection)), mat.shininess);
    vec3 specular = vec3(texture(mat.specular,uv)) * specularFactor * light.spec;

    vec3 emission = vec3(0.0f);
    if(texture(mat.specular,uv).x<0.1f)
    emission = vec3(texture(mat.emission,uv));

    vec3 resultant = ambient + diffuse + specular + emission;
    FragColor = vec4(resultant.xyz, 1.0f);
}
