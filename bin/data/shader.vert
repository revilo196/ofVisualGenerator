#version 450

//from OF
uniform mat4 modelViewProjectionMatrix;
in vec4 position;
in vec2 texcoord;

uniform float time;

out vec2 texCoordVarying;

void main(){
  gl_Position =  modelViewProjectionMatrix * position;
  texCoordVarying = texcoord;
}
