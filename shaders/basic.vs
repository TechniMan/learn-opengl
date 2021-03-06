#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 nrm;

uniform mat4 world;
uniform mat4 view;
uniform mat4 proj;

out vec3 vertexWorldPosition;
out vec3 vertexNormal;

void main()
{
    vec4 worldPos = world * vec4(pos, 1.0);
    gl_Position = proj * view * worldPos;
    
    vertexWorldPosition = vec3(worldPos);
    vertexNormal = mat3(transpose(inverse(world))) * nrm;
}
