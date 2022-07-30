attribute vec2 vertexPosition;
// attribute vec2 vertexUV;
// attribute vec3 vertexNormal;

varying vec2 uv;
varying vec2 uv_blur[11];

// uniform mat4 projMatrix;
// uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

uniform float horResolution;

void main()
{
    // vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    // gl_Position = projMatrix * viewMatrix * vertexWorldPosition;
    gl_Position = transformMatrix * vec4(vertexPosition, 0.0, 1.0);

    // x: -1 ~ 1 ==> 0 ~ 1
    // y: -1 ~ 1 ==> 0 ~ 1
    uv = vec2((1.0 + vertexPosition.x) / 2.0, (1.0 + vertexPosition.y) / 2.0);

    float pixelWidth = 1.0 / horResolution;

    for (int i = -5; i <= 5; i++) {
        uv_blur[i + 5] = uv + vec2(pixelWidth * i, 0.0);
    }
}
