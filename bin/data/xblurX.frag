
uniform sampler2DRect tex0;
uniform vec2 format;
uniform float blurAmnt;
uniform float glowAmnt;

in vec2 v_texcoord;
out vec4 outputColor;

void main()
{
    vec4 color;

    float blurx = blurAmnt * 4;

    color += 1.0 * texture(tex0, v_texcoord + vec2(blurx * -4.0, 0.0));
    color += 2.0 * texture(tex0, v_texcoord + vec2(blurx * -3.0, 0.0));
    color += 3.0 * texture(tex0, v_texcoord + vec2(blurx * -2.0, 0.0));
    color += 4.0 * texture(tex0, v_texcoord + vec2(blurx * -1.0, 0.0));

    color += 5.0 * texture(tex0, v_texcoord + vec2(blurx, 0));

    color += 4.0 * texture(tex0, v_texcoord + vec2(blurx * 2.0, 0.0));
    color += 3.0 * texture(tex0, v_texcoord + vec2(blurx * 2.0, 0.0));
    color += 2.0 * texture(tex0, v_texcoord + vec2(blurx * 3.0, 0.0));
    color += 1.0 * texture(tex0, v_texcoord + vec2(blurx * 4.0, 0.0));

    color /= (25.0);
    color.a = 1;
    outputColor = color;
}
