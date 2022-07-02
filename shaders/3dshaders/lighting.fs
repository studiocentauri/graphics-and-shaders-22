#version 330 core

struct Material {
    vec3 ambience;
    vec3 diffuse;
    vec3 specular;
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
uniform vec3 viewPos;
in vec3 normal;
in vec2 uv;
in vec3 position;
uniform sampler2D tex;
void main() {
    vec3 ambient = mat.ambience * light.amb;

    vec3 norm = normalize(normal);
    vec3 incident = normalize(light.pos - position);

    float diffuseFactor = max(0, dot(norm, incident));
    vec3 diffuse = mat.diffuse * diffuseFactor * light.diff;

    vec3 reflected = normalize(reflect(-incident, norm));
    vec3 viewDirection = normalize(viewPos - position);

    float specularFactor = pow(max(0, dot(reflected, viewDirection)), mat.shininess);
    vec3 specular = mat.specular * specularFactor * light.spec;

    vec3 resultant = ambient + diffuse + specular;
    FragColor = vec4(resultant.xyz, 1.0f);
}
