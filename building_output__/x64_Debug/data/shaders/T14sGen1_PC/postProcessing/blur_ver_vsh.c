attribute vec2 vertexPosition;
// attribute vec2 vertexUV;
// attribute vec3 vertexNormal;

varying vec2 uv;
varying vec2 uv_blur[11];

// uniform mat4 projMatrix;
// uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

uniform float verResolution;

void main()
{
    // vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    // gl_Position = projMatrix * viewMatrix * vertexWorldPosition;
    gl_Position = transformMatrix * vec4(vertexPosition, 0.0, 1.0);

    // x: -1 ~ 1 ==> 0 ~ 1
    // y: -1 ~ 1 ==> 0 ~ 1
    uv = vec2((1.0 + vertexPosition.x) / 2.0, (1.0 + vertexPosition.y) / 2.0);

    float pixelHeight = 1.0 / verResolution;

    for (int i = -5; i <= 5; i++) {

    	uv_blur[i + 5] = uv + vec2(0.0, pixelHeight * i);

        // Blurred model gets further from original model as camera moves
        //
        // if (uv_blur[i + 5].y > 1.0) {
        //     uv_blur[i + 5].y = 1.0;
        // }
        // else if (uv_blur[i + 5].y < 0.0) {
        //     uv_blur[i + 5].y = 0.0;
        // }
    }
}
