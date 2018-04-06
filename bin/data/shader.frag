#version 450

//from OF
uniform vec4 globalColor;


out vec4 outputColor;
uniform float time;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.

    float windowWidth = 1024.0;
    float windowHeight = 768.0;

    float r = (gl_FragCoord.x/ windowWidth) * (sin(time)+1) *globalColor.r;
    float g = (gl_FragCoord.y / windowHeight) * (cos(time*0.7 + 1.5)+1) * globalColor.g;
    float b = 1.0 *  (sin(time *1.1+ 4.6 )+1) *globalColor.b;
    float a = 1.0;
    outputColor = vec4(r,g,b,a);
}
