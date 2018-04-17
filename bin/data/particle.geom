#version 450

layout (points) in;
layout (triangle_strip, max_vertices = 8) out;

in vec4 baseColour[];

out vec4 colour;

uniform mat4 modelViewProjectionMatrix;

void main()
{

	vec4 offset = vec4(-1.0, 1.0, 0.0, 0.0);
	vec4 vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = modelViewProjectionMatrix * vertexPos;
	colour = baseColour[0];
	EmitVertex();

	offset = vec4(-1.0, -1.0, 0.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position =modelViewProjectionMatrix * vertexPos;
	colour = baseColour[0];
	EmitVertex();

	offset = vec4(1.0, 1.0, 0.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = modelViewProjectionMatrix * vertexPos;
	colour = baseColour[0];
	EmitVertex();

	offset = vec4(1.0, -1.0, 0.0, 0.0);
	vertexPos = offset + gl_in[0].gl_Position;
	gl_Position = modelViewProjectionMatrix * vertexPos;
	colour = baseColour[0];
	EmitVertex();

	EndPrimitive();
}
