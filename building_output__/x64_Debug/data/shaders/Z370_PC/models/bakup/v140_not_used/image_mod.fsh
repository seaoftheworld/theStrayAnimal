#version 140

// in vec3 color;
in vec2 uv;

// uniform float blendAlpha = 1.0f;
// uniform float blendAlpha;

uniform sampler2D texture_sampler;

// out vec3 o_pixelColor;
out vec4 o_pixelColor;

void main()
{
    // color = texture(texture_sampler, uv);
    // color.a = blendAlpha;

    // gl_FragColor = texture2D(texture_sampler, uv);
    // gl_FragColor.a = blendAlpha;

    // gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    // gl_FragColor = texture2D(texture_sampler, uv);

    // vec4 color = texture2D(texture_sampler, uv);
    vec4 color = texture(texture_sampler, uv);

    if (color.a < 0.1) {
        discard;
    }

    o_pixelColor = color;
}
