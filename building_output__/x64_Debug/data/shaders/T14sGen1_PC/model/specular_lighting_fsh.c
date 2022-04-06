#version 330

in vec3 vertexSurface;
in vec2 uv;
in vec3 vertexToCamera;
in vec3 vertexToLight;

uniform sampler2D texture_sampler;
uniform float reflectivity;
uniform float shineDamper;
uniform vec3 lightColor;

out vec4 out_pixelColor;

void main()
{
    // color = texture(texture_sampler, uv);
    // color.a = blendAlpha;

    // gl_FragColor = texture2D(texture_sampler, uv);
    // gl_FragColor.a = blendAlpha;

    // gl_FragColor = texture2D(texture_sampler, uv);
    // gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);

    vec3 unitVertexSurface = normalize(vertexSurface);
    vec3 unitVertexToLight = normalize(vertexToLight);

    vec3 diffuse; {
        float dot_result = dot(unitVertexSurface, unitVertexToLight);
        float brightness = max(dot_result, 0.2);
        diffuse = brightness * lightColor;
    }

    vec3 specular; {
        vec3 vertexReflectedLight = reflect(-unitVertexToLight, unitVertexSurface);
        vec3 unitVertexToCamera = normalize(vertexToCamera);

        float specularFactor = dot(vertexReflectedLight, unitVertexToCamera);
        specularFactor = max(specularFactor, 0.0);

        float dampedFactor = pow(specularFactor, shineDamper);
        specular = dampedFactor * lightColor;
    }

    // gl_FragColor = vec4(diffuse, 1.0) * texture2D(texture_sampler, uv);
    // vec4 color = vec4(diffuse, 1.0) * texture2D(texture_sampler, uv);
    vec4 color = vec4(diffuse, 1.0) * texture(texture_sampler, uv);
    if (color.a < 0.1) {
        discard;
    }
    color = color + vec4(specular, 1.0);

    out_pixelColor = color;
}
