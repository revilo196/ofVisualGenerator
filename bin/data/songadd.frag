#version 450

uniform sampler2DRect mtex0;

in vec2 texCoordVarying;

out vec4 outputColor;

void main()
{


  vec4 c0 = texture(mtex0, gl_FragCoord.xy).rgba * vec4(1,1,1,0.25);

  outputColor = c0;


}
