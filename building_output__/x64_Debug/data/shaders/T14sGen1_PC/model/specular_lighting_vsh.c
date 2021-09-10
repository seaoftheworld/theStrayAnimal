#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

out vec3 vertexSurface;
out vec3 vertexToLight;
out vec3 vertexToCamera;
out vec2 uv;

// uniform float tFloat;
uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

uniform vec3 lightPosition;

void main()
{
    // gl_Position.xyz = vertexPosition;
    // gl_Position.x += tFloat;
    // gl_Position.w = 1.0;
    // gl_Position.xyz = vertexPosition;

    vertexSurface = (transformMatrix * vec4(vertexNormal, 0.0)).xyz;
    vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * viewMatrix * vertexWorldPosition;

    vertexToLight = lightPosition - vertexWorldPosition.xyz;
    vertexToCamera = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - vertexWorldPosition.xyz;
    uv = vertexUV;
}
