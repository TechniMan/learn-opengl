#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

uniform float time;

out vec4 vertexColour;

void main()
{
    gl_Position = vec4(pos.x + sin(time), pos.y - cos(time * 0.5f), pos.z, 1.0);
    //vertexColour = vec4(col, 1.0);
    vertexColour = (gl_Position + 1.0f) * 0.5f;
}
