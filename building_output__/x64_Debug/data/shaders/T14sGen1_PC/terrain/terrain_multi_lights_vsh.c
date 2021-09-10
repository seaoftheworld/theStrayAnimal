#version 330

// Inputs
in vec3 vertexPosition;
in vec2 vertexUV;
in vec3 vertexNormal;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

uniform vec3 lightPosition[8];

// To fragment shader
out vec2 uv;

out vec3 vertexSurface;
out vec3 vertexToLight[8];
out vec3 vertexToCamera;

void main()
{
    vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * viewMatrix * vertexWorldPosition;

    uv = vertexUV;

    vertexSurface = (transformMatrix * vec4(vertexNormal, 0.0)).xyz;

    vertexToCamera = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - vertexWorldPosition.xyz;
    
    for (int i = 0; i < 8; i++) {
    // for (int i = 0; i < 1; i++) {
        vertexToLight[i] = lightPosition[i] - vertexWorldPosition.xyz;
    }
    // vertexToLight0 = lightPosition0 - vertexWorldPosition.xyz;
    // vertexToLight1 = lightPosition1 - vertexWorldPosition.xyz;
}
