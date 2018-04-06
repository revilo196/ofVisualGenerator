#version 450

//from OF
uniform vec4 globalColor;


out vec4 outputColor;
uniform float time;

void main()
{
    outputColor = globalColor;
}
