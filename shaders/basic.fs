#version 330 core
in vec4 vertexColour;

out vec4 fragColour;

void main()
{
    //vec4(1.0 - 0.3922, 1.0 - 0.5843, 1.0 - 0.9294, 1.0)
    fragColour = vertexColour;
}
