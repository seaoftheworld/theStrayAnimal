#version 140

in vec3 vertexPosition;
// in vec2 vertexUV;
const vec3 vertexColor = vec3(1.0, 0.0, 0.0);

// out vec2 uv;
out vec3 color;

// uniform float tFloat;
// uniform mat4 mvp;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

void main()
{
    // gl_Position.xyz = vertexPosition;
    // gl_Position.x += tFloat;
    // gl_Position.w = 1.0;
    // gl_Position.xyz = vertexPosition;

    // gl_Position = mvp * vec4(vertexPosition, 1.0);
    // gl_Position = vec4(vertexPosition, 1.0);

    // gl_Position = transformMatrix * vec4(vertexPosition, 1.0);
    vec4 worldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * viewMatrix * worldPosition;

    // uv = vertexUV;
    color = vertexColor;
}
