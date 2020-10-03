

//from OF
uniform vec4 globalColor;
uniform float u_time;        // shader playback time (in seconds)
uniform float u_delta;       // delta time between frames (in seconds)
uniform vec4 u_date;        // year, month, day and seconds
uniform vec2 u_resolution;  // viewport resolution (in pixels)
uniform vec2 u_mouse;       // mouse pixel coords

uniform sampler2DRect mtex0;
uniform float freq;
uniform float disort;
uniform float s_time;


in vec2 v_texcoord;
out vec4 outputColor;



void main()
{

    outputColor = texture(mtex0, v_texcoord + vec2(disort*sin(freq*v_texcoord.y + s_time ),0));

}
