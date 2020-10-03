
uniform sampler2DRect tex0;
uniform vec2 format;
uniform float blurAmnt;
uniform float glowAmnt;
in vec2 v_texcoord;
out vec4 outputColor;


void main()
{
    vec4 color;

    float blurx = blurAmnt * 10;

    color += 1.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * -4.0));
    color += 2.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * -3.0));
    color += 3.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * -2.0));
    color += 4.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * -1.0));

    color += 5.0 * texture(tex0, v_texcoord + vec2(0.0,blurx));

    color += 4.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * 1.0));
    color += 3.0 * texture(tex0, v_texcoord + vec2(0.0,blurx * 2.0));
    color += 2.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * 3.0));
    color += 1.0 * texture(tex0, v_texcoord + vec2(0.0, blurx * 4.0));

    color /= (25.0 -0.5);
    color.a = 1;
   // color = vec4(0.5,0.0,0,1.0);
    outputColor = color;
}
