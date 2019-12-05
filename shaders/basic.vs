#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;
layout (location = 2) in vec2 tex;

uniform mat4 transform;

out vec4 vertexColour;
out vec2 vertexTexCoord;

void main()
{
    gl_Position = transform * vec4(pos, 1.0);
    //vertexColour = vec4(col, 1.0);
    vertexColour = (gl_Position + 1.0) * 0.5;
    vertexTexCoord = tex;
}
