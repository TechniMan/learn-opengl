#version 330 core
struct Material {
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};
struct Light {
    vec3 Position;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
};

in vec3 vertexWorldPosition;
in vec3 vertexNormal;

uniform Material material;
uniform Light light;
uniform vec3 eyePos;

out vec4 fragColour;

void main()
{
    vec3 ambient = light.Ambient * material.Ambient;

    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(light.Position - vertexWorldPosition);
    vec3 diffuse = light.Diffuse * max(dot(normal, lightDir), 0.0) * material.Diffuse;

    vec3 eyeDir = normalize(eyePos - vertexWorldPosition);
    vec3 reflection = reflect(-lightDir, normal);
    float spec = pow(max(dot(eyeDir, reflection), 0.0), 32);
    vec3 specular = light.Specular * spec * material.Specular;
    
    vec3 result = ambient + diffuse + specular;
    fragColour = vec4(result, 1.0);
}
