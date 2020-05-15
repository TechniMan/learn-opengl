#version 330 core
in vec4 vertexColour;
in vec3 vertexWorldPosition;
in vec3 vertexNormal;
in vec2 vertexTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float time;
uniform vec3 lightPos;
uniform vec3 lightColour;
uniform vec3 objectColour;
uniform vec3 eyePos;
uniform vec3 eyeDir;

out vec4 fragColour;

void main()
{
    vec3 ambient = lightColour * 0.1;

    vec3 lightDir = normalize(lightPos - vertexWorldPosition);
    vec3 diffuse = lightColour * max(dot(normalize(vertexNormal), lightDir), 0.0);
    
    vec3 result = objectColour * (ambient + diffuse);
    fragColour = vec4(result, 1.0);
    //vec4(1.0 - 0.3922, 1.0 - 0.5843, 1.0 - 0.9294, 1.0)
    //fragColour = vertexColour * texture(texture0, vertexTexCoord) + mix(vec4(0.0, 0.0, 0.0, 1.0), texture(texture1, vertexTexCoord), abs(sin(time)) * 0.1);
}
