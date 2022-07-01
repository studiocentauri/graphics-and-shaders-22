#version 330 core

struct Material
{
    float ambience;
    float diffuse;
    float specular;
    float shininess;

};
uniform Material mat;
out vec4 FragColor;
uniform vec3 col;
uniform vec3 ambientLight;
uniform vec3 lightPos;
uniform vec3 viewPos;
in vec3 normal;
in vec2 uv;
in vec3 position;
uniform sampler2D tex;
void main()
{
    vec3 objectColor = col;
    vec3 lightColor = ambientLight;

    vec3 ambient = objectColor * mat.ambience * lightColor;
    
    vec3 norm = normalize(normal);
    vec3 incident = normalize(lightPos-position);
    
    float diffuseLight = max(0,dot(norm,incident));
    vec3 diffuse = objectColor * mat.diffuse * diffuseLight*lightColor;

    vec3 reflected  = normalize(reflect(-incident,norm));
    vec3 viewDirection = normalize(viewPos-position);

    float specularLight = pow(max(0,dot(reflected,viewDirection)),mat.shininess);
    vec3 specular = objectColor * mat.specular * specularLight * lightColor;

    vec3 resultant = ambient+diffuse+specular;
    FragColor = vec4(resultant.xyz, 1.0f);
}
