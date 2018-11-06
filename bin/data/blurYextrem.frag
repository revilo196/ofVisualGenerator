#version 450

uniform sampler2DRect tex0;
uniform vec2 format;
uniform float blurAmnt;
uniform float glowAmnt;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    vec4 color;

    vec2 texCoord = texCoordVarying * format;

    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -8.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -7.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -6.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -5.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -4.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -3.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -2.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * -1.0));

    color += 5.0 * texture(tex0, texCoord + vec2(0.0,blurAmnt *0));

    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 1.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0,blurAmnt * 2.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 3.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 4.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 5.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0,blurAmnt * 6.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 7.0));
    color += 5.0 * texture(tex0, texCoord + vec2(0.0, blurAmnt * 8.0));

    color /= (25.0-glowAmnt);

    outputColor = min(color-0.15, 1);
}
