#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nrm;
layout (location = 2) in vec2 tex;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

out vec4 vertexColour;
out vec3 vertexWorldPosition;
out vec3 vertexNormal;
out vec2 vertexTexCoord;

void main()
{
    vec4 worldPos = world * vec4(pos, 1.0);
    gl_Position = proj * view * worldPos;
    
    vertexColour = normalize(worldPos);
    vertexWorldPosition = vec3(worldPos);
    vertexNormal = normalize(nrm);
    vertexTexCoord = tex;
}
