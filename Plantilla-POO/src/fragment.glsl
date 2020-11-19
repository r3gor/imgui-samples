#version 330

out vec4 fragColor;
uniform vec3 u_color;
uniform int multicolor;

in vec4 varColor;

void main() {
    if (multicolor == 0)
        fragColor = vec4(u_color, 1.0);
    if (multicolor == 1)
        fragColor = varColor;
}