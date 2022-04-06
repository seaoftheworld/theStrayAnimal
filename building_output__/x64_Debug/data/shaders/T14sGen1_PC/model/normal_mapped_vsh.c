#version 330
// #version 150

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal;
layout(location = 3) in vec3 tangent;

// in vec3 vertexPosition;  // doesn't work
// in vec2 vertexUV;
// in vec3 vertexNormal;
// in vec3 tangent;

uniform mat4 projMatrix;
uniform mat4 viewMatrix;
uniform mat4 transformMatrix;

// const vec4 plane = vec4(0, 0, -1, 1.5);
// uniform vec4 plane;
uniform vec3 lightPosition[8];

// To fragment shader
// out vec3 vertexSurface;
out vec3 vertexToCamera;
out vec3 vertexToLight[8];
out vec2 uv;
// out vec3 f_tangent;

void main()
{
    // vec4 vertexWorldPosition = transformMatrix * vec4(vertexPosition, 1.0);
    // gl_Position = projMatrix * viewMatrix * vertexWorldPosition;
    // gl_ClipDistance[0] = dot(vertexWorldPosition, plane);

    uv = vertexUV;
    // f_tangent = tangent;

    mat4 modelViewMat = viewMatrix * transformMatrix;
    vec4 posRelativeToCam = modelViewMat * vec4(vertexPosition, 1.0);
    gl_Position = projMatrix * posRelativeToCam;

    // assign value for mat3 toTangentSapce
    vec3 vertexSurface = (modelViewMat * vec4(vertexNormal, 0.0)).xyz;
        vec3 norm = normalize(vertexSurface);
        vec3 tang = normalize(tangent);
        vec3 bitang = normalize(cross(norm, tang));
    mat3 toTangentSapce = mat3(
        tang.x, bitang.x, norm.x,
        tang.y, bitang.y, norm.y,
        tang.z, bitang.z, norm.z
    );

    // vertexToCamera = (inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - vertexWorldPosition.xyz;
    vertexToCamera = toTangentSapce * (-posRelativeToCam.xyz);
    for (int i = 0; i < 8; i++) {
        // vertexToLight[i] = toTangentSapce * () lightPosition[i] - vertexWorldPosition.xyz;
        vertexToLight[i] = toTangentSapce * (lightPosition[i] - posRelativeToCam.xyz);
    }
}
