#version 330 core
in vec4 vertexColour;
in vec2 vertexTexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform float time;

out vec4 fragColour;

void main()
{
    //vec4(1.0 - 0.3922, 1.0 - 0.5843, 1.0 - 0.9294, 1.0)
    //fragColour = vertexColour * mix(texture(texture0, vertexTexCoord), texture(texture1, vertexTexCoord), abs(sin(time)) * 0.5);
    fragColour = vertexColour * texture(texture0, vertexTexCoord) + mix(vec4(0.0, 0.0, 0.0, 1.0), texture(texture1, vertexTexCoord), abs(sin(time)) * 0.1);
}
