#version 450

in vec3 position;
in vec4 colour;

uniform vec4 mainColor;

out vec4 baseColour;

void main(void){

	gl_Position = vec4(position,1.0);
	baseColour = colour * mainColor;

}
