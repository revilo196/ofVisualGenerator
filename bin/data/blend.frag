#version 450

uniform sampler2DRect mtex0;
uniform sampler2DRect mtex1;

uniform int mode;

// this comes from the vertex shader
in vec2 texCoordVarying;

out vec4 outputColor;

//used from vvvv blend.fx+
#define saturate(v) clamp(v,0.0,1.0)
#define bld(op,c0,c1) vec4(mix((c0*c0.a+c1*c1.a*(1-c0.a))/saturate(c0.a+c1.a*(1-c0.a)),(op),c0.a*c1.a).rgb,saturate(c0.a+c1.a*(1-c0.a)))

void main()
{
  vec4 c0 = texture(mtex0,gl_FragCoord.xy).rgba;
  vec4 c1 = texture(mtex1,gl_FragCoord.xy).rgba;

  if(mode == 0)  {//add
    outputColor = bld(c0+c1,c0,c1);
  } else if (mode == 1) { // mul
    outputColor = bld(c0*c1,c0,c1);
  } else if (mode == 2) { // screen
    outputColor = bld(c0+c1*saturate(1-c0),c0,c1);
  } else if (mode == 3) { // normal
    outputColor = bld(c1,c1,c0);
  } else if (mode == 4) { // diff
    outputColor = bld(abs(c0-c1),c0,c1);
  }

}
