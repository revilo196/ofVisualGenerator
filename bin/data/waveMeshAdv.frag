#version 450
#define M_PI 3.1415926535897932384626433832795

uniform float freq;
uniform float size;
uniform float zToSize;
uniform float zToColor;

out vec4 outputColor;

in float zOff;
in vec4 color;
in vec2 texCoordVarying;

void main()
{
  float sizem = size + ((zOff) * zToSize);
  float st = 1 - sizem;

  float fx = sin(texCoordVarying.x * M_PI * 2 * freq);
  float fy = sin(texCoordVarying.y * M_PI * 2 * freq);

  fx = clamp(fx, 0.0, 1.0);
  fy = clamp(fy, 0.0, 1.0);



  vec3 outcolor = color.rgb * step(st,  (fx*fy)) * (1 + (zOff)*zToColor);
   outputColor = vec4(outcolor, 1.0);
}
