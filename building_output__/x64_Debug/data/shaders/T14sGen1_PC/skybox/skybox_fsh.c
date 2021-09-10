uniform samplerCube cube;
in vec3 uv;

// out vec4 out_color;

void main() {
    vec4 color = texture(cube, uv);
    gl_FragColor = color;
}
