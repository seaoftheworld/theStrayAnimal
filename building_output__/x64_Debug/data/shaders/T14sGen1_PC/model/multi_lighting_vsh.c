#version 330

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

// const vec4 plane = vec4(0, 0, -1, 1.5);
uniform vec4 plane;
uniform vec3 lightPosition[8];

// To fragment shader
out vec3 vertexToCamera;

// noperspective out vec3 vertexSurface;
// flat out vec3 vertexSurface;
out vec3 vertexSurface;

out vec2 uv;
out vec3 vertexToLight[8];

void main()
{
    vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * viewMatrix * vertexWorldPosition;

    gl_ClipDistance[0] = dot(vertexWorldPosition, plane);

    vertexToCamera = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - vertexWorldPosition.xyz;
    vertexSurface = (transformMatrix * vec4(vertexNormal, 0.0)).xyz;
    uv = vertexUV;
    
    for (int i = 0; i < 8; i++) {
        vertexToLight[i] = lightPosition[i] - vertexWorldPosition.xyz;
    }
}
