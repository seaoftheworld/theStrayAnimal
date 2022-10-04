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

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[0].x > 0.0 && uv_blur[0].x < 1.0 && \
		uv_blur[0].y > 0.0 && uv_blur[0].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[0]; {

			// if (uv_blur[0].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[0].x) * 0.98;
			// }
			// if (uv_blur[0].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[0].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.0093;
		// color += texture(guiTexture, uv_blur[0]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[1].x > 0.0 && uv_blur[1].x < 1.0 && \
		uv_blur[1].y > 0.0 && uv_blur[1].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[1]; {

			// if (uv_blur[1].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[1].x) * 0.98;
			// }
			// if (uv_blur[1].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[1].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.028002;
		// color += texture(guiTexture, uv_blur[1]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[2].x > 0.0 && uv_blur[2].x < 1.0 && \
		uv_blur[2].y > 0.0 && uv_blur[2].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[2]; {

			// if (uv_blur[2].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[2].x) * 0.98;
			// }
			// if (uv_blur[2].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[2].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.065984;
		// color += texture(guiTexture, uv_blur[2]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[3].x > 0.0 && uv_blur[3].x < 1.0 && \
		uv_blur[3].y > 0.0 && uv_blur[3].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[3]; {

			// if (uv_blur[3].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[3].x) * 0.98;
			// }
			// if (uv_blur[3].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[3].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.121703;
		// color += texture(guiTexture, uv_blur[3]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[4].x > 0.0 && uv_blur[4].x < 1.0 && \
		uv_blur[4].y > 0.0 && uv_blur[4].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[4]; {

			// if (uv_blur[4].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[4].x) * 0.98;
			// }
			// if (uv_blur[4].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[4].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.175713;
		// color += texture(guiTexture, uv_blur[4]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[5].x > 0.0 && uv_blur[5].x < 1.0 && \
		uv_blur[5].y > 0.0 && uv_blur[5].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[5]; {

			// if (uv_blur[5].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[5].x) * 0.98;
			// }
			// if (uv_blur[5].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[5].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.198596;
		// color += texture(guiTexture, uv_blur[5]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[6].x > 0.0 && uv_blur[6].x < 1.0 && \
		uv_blur[6].y > 0.0 && uv_blur[6].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[6]; {

			// if (uv_blur[6].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[6].x) * 0.98;
			// }
			// if (uv_blur[6].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[6].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.175713;
		// color += texture(guiTexture, uv_blur[6]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[7].x > 0.0 && uv_blur[7].x < 1.0 && \
		uv_blur[7].y > 0.0 && uv_blur[7].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[7]; {

			// if (uv_blur[7].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[7].x) * 0.98;
			// }
			// if (uv_blur[7].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[7].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.121703;
		// color += texture(guiTexture, uv_blur[7]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[8].x > 0.0 && uv_blur[8].x < 1.0 && \
		uv_blur[8].y > 0.0 && uv_blur[8].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[8]; {

			// if (uv_blur[8].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[8].x) * 0.98;
			// }
			// if (uv_blur[8].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[8].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.065984;
		// color += texture(guiTexture, uv_blur[8]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[9].x > 0.0 && uv_blur[9].x < 1.0 && \
		uv_blur[9].y > 0.0 && uv_blur[9].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[9]; {

			// if (uv_blur[9].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[9].x) * 0.98;
			// }
			// if (uv_blur[9].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[9].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.028002;
		// color += texture(guiTexture, uv_blur[9]);
	}

	// if (uv_blur[0].x >= 0.0 && uv_blur[0].x <= 1.0) {
	// if (uv_blur[0].x >= 0.0) 
	if (uv_blur[10].x > 0.0 && uv_blur[10].x < 1.0 && \
		uv_blur[10].y > 0.0 && uv_blur[10].y < 1.0) 
	{
		vec2 uv_blur_mod = uv_blur[10]; {

			// if (uv_blur[10].x < 0.5) {
			// 	uv_blur_mod.x = 0.5 - (0.5 - uv_blur[10].x) * 0.98;
			// }
			// if (uv_blur[10].x > 0.5) {
			// 	uv_blur_mod.x = 0.5 + (uv_blur[10].x - 0.5) * 0.98;
			// }
		}

		color += texture(guiTexture, uv_blur_mod) * 0.0093;
		// color += texture(guiTexture, uv_blur[9]);
	}

	// color.rgb = pow(color.rgb, vec3(1.0 / 1.4));  // increases apple's flickering
	color.rgb = pow(color.rgb, vec3(1.0 / 1.2)); 
	gl_FragColor = color;
}
