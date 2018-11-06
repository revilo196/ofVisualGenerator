#version 450

uniform sampler2DRect tex0;
uniform float blurAmnt;
uniform float glowAmnt;
uniform vec2 format;
in vec2 texCoordVarying;
out vec4 outputColor;

void main()
{
    vec4 color;

    vec2 texCoord = texCoordVarying * format;

    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -8.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -7.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -6.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -5.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -4.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -3.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -2.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * -1.0, 0.0));

    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt*0, 0));

    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 1.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 2.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 3.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 4.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 5.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 6.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 7.0, 0.0));
    color += 5.0 * texture(tex0, texCoord + vec2(blurAmnt * 8.0, 0.0));

    color /= (25.0-glowAmnt);
    color = min(color-0.15, 1);
    float minCL = min(color.r,color.g);
    minCL = min(minCL, color.b);

    outputColor = vec4(minCL,minCL,minCL,color.a);
    //outputColor = min(color-0.15, 1);
}
