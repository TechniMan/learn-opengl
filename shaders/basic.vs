#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

uniform float time;

out vec4 vertexColour;
out vec2 vertexTexCoord;

void main()
{
    gl_Position = vec4((pos.x + sin(time)) * 0.5, (pos.y - cos(time * 0.5f)) * 0.5, pos.z, 1.0);
    //vertexColour = vec4(col, 1.0);
    vertexColour = (gl_Position + 1.0) * 0.5;
    vertexTexCoord = tex;
}
