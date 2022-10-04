uniform sampler2D guiTexture;

// From v-shader
varying vec2 uv;
// out vec4 out_color;

const float contrast = 0.9;

void main()
{
    // vec4 color = texture2D(guiTexture, vec2(uv.x, uv.y));
    // vec4 color = texture2D(guiTexture, uv);
    // vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
    vec4 color = texture(guiTexture, uv);
    // color.rgb = (color.rgb - 0.5) * (1.0 + contrast) + 0.5;

    // out_color = color;
    gl_FragColor = color;
}
