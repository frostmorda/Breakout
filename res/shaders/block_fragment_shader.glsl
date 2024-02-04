#version 460
in vec2 tex;
out vec4 FragColor;
uniform sampler2D image;
uniform vec3 color;

void main()
{
    vec4 tex_color = vec4(color, 1.0) * texture(image, tex);
    if (tex_color.a < 0.1) {
        discard;
    }
    FragColor = tex_color;
}