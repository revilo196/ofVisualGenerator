#version 450
//from OF

out vec4 outputColor;
uniform float xpos;
uniform float ypos;
uniform float zpos;
in vec4 color;
#define MOD3 vec3(.1031,.11369,.13787)

vec3 hash33(vec3 p3)
{
	p3 = fract(p3 * MOD3);
    p3 += dot(p3, p3.yxz+19.19);
    return -1.0 + 2.0 * fract(vec3((p3.x + p3.y)*p3.z, (p3.x+p3.z)*p3.y, (p3.y+p3.z)*p3.x));
}

float perlin_noise(vec3 p)
{
    vec3 pi = floor(p);
    vec3 pf = p - pi;

    vec3 w = pf * pf * (3.0 - 2.0 * pf);

    return 	mix(
        		mix(
                	mix(dot(pf - vec3(0, 0, 0), hash33(pi + vec3(0, 0, 0))),
                        dot(pf - vec3(1, 0, 0), hash33(pi + vec3(1, 0, 0))),
                       	w.x),
                	mix(dot(pf - vec3(0, 0, 1), hash33(pi + vec3(0, 0, 1))),
                        dot(pf - vec3(1, 0, 1), hash33(pi + vec3(1, 0, 1))),
                       	w.x),
                	w.z),
        		mix(
                    mix(dot(pf - vec3(0, 1, 0), hash33(pi + vec3(0, 1, 0))),
                        dot(pf - vec3(1, 1, 0), hash33(pi + vec3(1, 1, 0))),
                       	w.x),
                   	mix(dot(pf - vec3(0, 1, 1), hash33(pi + vec3(0, 1, 1))),
                        dot(pf - vec3(1, 1, 1), hash33(pi + vec3(1, 1, 1))),
                       	w.x),
                	w.z),
    			w.y);
}


float noise_sum(vec3 p)
{
    float f = 0.0;
    p = p * 4.0;
    f += 1.0000 * perlin_noise(p); p = 2.0 * p;
    f += 0.5000 * perlin_noise(p); p = 2.0 * p;
	  f += 0.2500 * perlin_noise(p); p = 2.0 * p;
	  f += 0.1250 * perlin_noise(p); p = 2.0 * p;
	  f += 0.0625 * perlin_noise(p); p = 2.0 * p;

    return f;
}

void main()
{
   vec2 p = vec2(gl_FragCoord.x*0.001 + xpos, gl_FragCoord.y*0.001 + ypos);

	 vec3 pos = vec3(p , zpos);
	 vec3 col = vec3(0.0, 0.0, 0.0);

	 float f = noise_sum(pos);

	 col = vec3(f* 0.5 + 0.5);

   outputColor = color;
}
