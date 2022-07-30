uniform sampler2D guiTexture;

// From v-shader
varying vec2 uv;
// out vec4 out_color;
varying vec2 uv_blur[11];

// const float contrast = 0.9;

void main()
{
	{
		/*
		// contrast
		//
	    // vec4 color = texture2D(guiTexture, vec2(uv.x, uv.y));
	    // vec4 color = texture2D(guiTexture, uv);
	    // vec4 color = vec4(1.0, 0.0, 0.0, 1.0);
	    vec4 color = texture(guiTexture, uv);
	    color.rgb = (color.rgb - 0.5) * (1.0 + contrast) + 0.5;

	    // out_color = color;
	    gl_FragColor = color;
		// */
	}

	vec4 color = vec4(0.0);
	color += texture(guiTexture, uv_blur[0]) * 0.0093;
	color += texture(guiTexture, uv_blur[1]) * 0.028002;
	color += texture(guiTexture, uv_blur[2]) * 0.065984;
	color += texture(guiTexture, uv_blur[3]) * 0.121703;
	color += texture(guiTexture, uv_blur[4]) * 0.175713;
	color += texture(guiTexture, uv_blur[5]) * 0.198596;
	color += texture(guiTexture, uv_blur[6]) * 0.175713;
	color += texture(guiTexture, uv_blur[7]) * 0.121703;
	color += texture(guiTexture, uv_blur[8]) * 0.065984;
	color += texture(guiTexture, uv_blur[9]) * 0.028002;
	color += texture(guiTexture, uv_blur[10]) * 0.0093;
	gl_FragColor = color;
}
