uniform sampler2D briTexture;

// From v-shader
varying vec2 uv;
// out vec4 out_color;

void main()
{
    // vec4 color = texture2D(briTexture, vec2(uv.x, uv.y));
    // vec4 color = texture2D(briTexture, uv);
    vec4 color = texture(briTexture, uv);
    // out_color = color;

    {
        // float brightness = (color.r * 0.2126) + (color.g * 0.7152) + (color.b * 0.0722);
        // float alpha = color.a;
        // gl_FragColor = color * brightness;
        // gl_FragColor.a = alpha;

        gl_FragColor = color;
    }
}
