uniform sampler2D guiTexture;

// From v-shader
varying vec2 uv;
// out vec4 out_color;

void main()
{
    // vec4 color = texture2D(guiTexture, vec2(uv.x, uv.y));
    // vec4 color = texture2D(guiTexture, uv);
    vec4 color = texture(guiTexture, uv);
    // out_color = color;
    gl_FragColor = color;
}
