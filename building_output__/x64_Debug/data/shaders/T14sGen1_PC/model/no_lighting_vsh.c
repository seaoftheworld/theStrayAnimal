#version 330
// If normal attribute co-exist with pos/uv, the display 
// is not correct without layout-quaulifier
// on the T14sGen1 PC.
//
// With layout-quaulifier, the version has to be 330,
// 130/140/150 (gl 3.0/3.1/3.3) doesn't support it.
//     in vec3 vertexPosition;
//     in vec2 vertexUV;
//     in vec3 vertexNormal;
//
layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
// layout(location = 2) in vec3 vertexNormal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

out vec2 uv;
// out vec3 normal;

void main()
{
    // gl_Position.xyz = vertexPosition;
    // gl_Position.x += tFloat;
    // gl_Position.w = 1.0;
    // gl_Position.xyz = vertexPosition;

    // gl_Position = mvp * vec4(vertexPosition, 1.0);
    // gl_Position = vec4(vertexPosition, 1.0);

    vec4 worldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * viewMatrix * worldPosition;

    uv = vertexUV;
}
