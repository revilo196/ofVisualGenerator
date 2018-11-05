#version 450

uniform sampler2DRect mtex0;
uniform sampler2DRect mtex1;

uniform int width;
uniform int height;

uniform int submodeA;
uniform int submodeB;


uniform int mode;
uniform float faderA;
uniform float faderB;
uniform int  invertA;
uniform int  invertB;
uniform int  tcd = 0;

uniform int black ;

// this comes from the vertex shader
in vec2 texCoordVarying;

out vec4 outputColor;

//used from vvvv blend.fx+
#define saturate(v) clamp(v,0.0,1.0)
#define bld(op,c0,c1) vec4(mix((c0*c0.a+c1*c1.a*(1-c0.a))/saturate(c0.a+c1.a*(1-c0.a)),(op),c0.a*c1.a).rgb,saturate(c0.a+c1.a*(1-c0.a)))

void main()
{
  vec2 invert = vec2(width, height);


  vec4 c0 = texture(mtex0, gl_FragCoord.xy).rgba * vec4(faderA,faderA,faderA,1);
  vec4 c1 = texture(mtex1, gl_FragCoord.xy).rgba * vec4(faderB,faderB,faderB,1);


  vec2 texCoord = texCoordVarying * vec2(width,height);

  if(tcd == 1) {

  c0 = texture(mtex0, texCoord).rgba * vec4(faderA,faderA,faderA,1);
  c1 = texture(mtex1, texCoord).rgba * vec4(faderB,faderB,faderB,1);

  }

  if(invertA == 1)
  {
    c0.rgb = (vec3(1,1,1) - c0.rgb);
  }

  if(invertB == 1)
  {
    c1.rgb = (vec3(1,1,1) - c1.rgb);
  }


  if(mode == 0)  {//add
    outputColor = bld(c0+c1,c0,c1);
    //outputColor = c0+c1//bld(c0+c1,c0,c1);

  } else if (mode == 1) { // mul
    outputColor = bld(c0*c1,c0,c1);
    if (submodeA == -1) {
        outputColor = c0 * c1;
    }
  } else if (mode == 2) { // screen
    outputColor = bld(c0+c1*saturate(1-c0),c0,c1);
  } else if (mode == 3) { // normal
    outputColor = (c0 * faderA + c1 * faderB);
  } else if (mode == 4) { // diff
    outputColor = bld(abs(c0-c1),c0,c1);
  }  else if (mode == 5) { //cherker
    int erg = int(floor(floor(gl_FragCoord.x) / (width / submodeA)));
    erg += int(floor(floor(gl_FragCoord.y) / (height / submodeB)));
    if (erg % 2 == 0 ) {
      outputColor = c0;
    } else {
      outputColor = c1;
    }
  }

  if (black == 1) {

    outputColor = vec4(0,0,0,1);

  }

}
