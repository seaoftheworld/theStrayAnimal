uniform sampler2D Texture00;
uniform sampler2D Texture01;

// From v-shader
varying vec2 uv;
// out vec4 out_color;

void main()
{
    // vec4 color = texture2D(Texture00, vec2(uv.x, uv.y));
    // vec4 color = texture2D(Texture00, uv);
    vec4 color_00 = texture(Texture00, uv);
    vec4 color_01 = texture(Texture01, uv);

    // out_color = color;
    // gl_FragColor = color_00;
    // gl_FragColor = color_01 * 4.0;

    gl_FragColor = color_00 + color_01 * 1.4;

    /*
    if (color_00.r < 0.1 && color_00.g < 0.1 && color_00.b < 0.1) {
    // if (color_00.b == 0.0) {
    	gl_FragColor = color_00 + color_01 * 2;
    }
    else {
    	gl_FragColor = color_00;
    }
    // */

    /*
    if (color_00.r > 0.2 || color_00.g > 0.2 || color_00.b > 0.2) {
    	gl_FragColor = color_00;
    }
    else {
    	// gl_FragColor = color_00 + color_01 * 2;
    	gl_FragColor = color_01;
    }
    // */

    /*
    // if (color_00.r < 0.3 && color_00.g < 0.3 && color_00.b < 0.3) {
    float avr = (color_00.r + color_00.g + color_00.b) / 3.0;
    if (avr == 0.0) {
    	gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else {
	    if (avr >= 0.2) {
	    	gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
	    	// gl_FragColor = color_00;
	    }
	    else if (avr >= 0.1 && avr < 0.2) {
	    	gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);
	    	// gl_FragColor = color_00;
	    }
	    else if (avr >= 0.05 && avr < 0.1) {
	    	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
	    }
	    else if (avr < 0.5) {
	    	gl_FragColor = vec4(0.0, 0.0, 1.0, 1.0);
	    	// gl_FragColor = color_01 * 4.0;
	    }
    }

    // if (color_00.r < 0.2) {
    // 	gl_FragColor = color_01 * 4.0;
    // }
    // else if (color_00.g < 0.2 && color_00.b < 0.2) {
    // 	gl_FragColor = color_01 * 4.0;
    // }
    // else {
    // 	gl_FragColor = color_00;
    // }
    // */
}
