#version 450

uniform sampler2DRect mtex0;
uniform vec2 textureSizem;

out vec4 outputColor;


in vec2 texCoordVarying;
in vec4 color;

void main()
{
  vec4 c0 = texture(mtex0,texCoordVarying*textureSizem).rgba;

   outputColor =  c0 * color;
}
