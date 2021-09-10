#version 140

// in vec2 uv;
in vec3 color;

// uniform sampler2D texSampler;
// uniform float blendAlpha = 1.0f;
// uniform float blendAlpha;

out vec3 o_pixelColor;

void main()
{
    // color = texture(texSampler, uv);
    // color.a = blendAlpha;

    // gl_FragColor = texture2D(texSampler, uv);
    // gl_FragColor.a = blendAlpha;

    // gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // gl_FragColor = texture2D(texSampler, uv);

    // vec4 color = texture2D(texSampler, uv);
    // if (color.a < 0.1) {
    //     discard;
    // }

    o_pixelColor = color;
}
