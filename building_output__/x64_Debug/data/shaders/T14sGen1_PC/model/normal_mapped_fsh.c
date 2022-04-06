// #version 150
#version 330

// Inputs
uniform sampler2D texture_sampler;
uniform sampler2D normal_map_sampler;

// uniform float blendAlpha = 1.0f;
// uniform float blendAlpha;
uniform vec3 lightAttenuation[8];
uniform vec3 lightColor[8];

uniform float reflectivity;
uniform float shineDamper;

// From v-shader
// noperspective in vec3 vertexSurface;
// flat in vec3 vertexSurface;
// in vec3 vertexSurface;
in vec3 vertexToLight[8];
in vec3 vertexToCamera;
in vec2 uv;
// in vec3 f_tangent;

out vec4 out_pixelColor;

void main()
{
    // vec3 unit_VertexSurface = normalize(vertexSurface);
    vec4 normal_map_val = 2 * texture(normal_map_sampler, uv) - 1.0;
    // vec3 unit_VertexSurface = normalize(vec3(1.0, 1.0, 1.0));
    vec3 unit_VertexSurface = normalize(normal_map_val.rgb);

    vec3 unit_VertexToCamera = normalize(vertexToCamera);
    vec3 sum_diffuse, sum_specular;

    for (int i = 0; i < 8; i++) {
        vec3 unit_VertexToLight = normalize(vertexToLight[i]);
        float lightDistance = length(vertexToLight[i]);
        float attFactor = lightAttenuation[i].x + lightDistance * lightAttenuation[i].y + lightDistance * lightDistance * lightAttenuation[i].z;

        // Assign value for sum_diffuse
        float brightness = dot(unit_VertexSurface, unit_VertexToLight);
        brightness = max(brightness, 0.2);
        sum_diffuse = sum_diffuse + brightness * lightColor[i] / attFactor;

        // Assign value for sum_diffuse
        vec3 vertexReflectedLight = reflect(-unit_VertexToLight, unit_VertexSurface);
        float specularFactor = dot(vertexReflectedLight, unit_VertexToCamera);
        specularFactor = max(specularFactor, 0.0);

        float dampedFactor = pow(specularFactor, shineDamper);
        sum_specular = sum_specular + dampedFactor * lightColor[i] / attFactor;
    }

    {
        // vec4 color = vec4(sum_diffuse, 1.0) * texture2D(texture_sampler, uv);
        vec4 color = vec4(sum_diffuse, 1.0) * texture(texture_sampler, uv);
        if (color.a < 0.1) {
            discard;
        }

        color = color + vec4(sum_specular, 1.0);
        out_pixelColor = color;

        // vec4 test_color = texture(normal_map_sampler, uv);
        // out_pixelColor = test_color;

        // out_pixelColor = vec4(f_tangent, 1.0);
        // out_pixelColor = vec4(unit_VertexSurface, 1.0);
    }
}
