#version 450

//from OF
uniform vec4 globalColor;

uniform int fullscreen;
uniform vec2 resulution;


uniform float time;

// Parameters
uniform float FREQUENCE ;
uniform float TILT ;
uniform float THIKNESS ;
uniform float SMOOTHNESS ;
//

in vec2 texCoordVarying;
out vec4 color;

#define _Smooth(p,r,s) smoothstep(-s, s, p-(r))
#define _thikness THIKNESS * .5

void main()
{

  float  tilt = TILT * FREQUENCE;

  vec2 U;
  if(fullscreen == 1)
  {
      U = gl_FragCoord.xy / resulution;
  } else {
      U = texCoordVarying;
  }
  float s = fract( dot(U, vec2(FREQUENCE,tilt)) + time );
  color = vec4( _Smooth(_thikness, abs(s - .5) ,SMOOTHNESS) ); // boldness
  color[3] = 1.0;
  color = color * globalColor;
}
