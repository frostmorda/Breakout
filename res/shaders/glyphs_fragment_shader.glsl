#version 460
in vec2 tex;
out vec4 FragColor;
uniform sampler2D image;
uniform vec3 color;

void main()
{
    FragColor = vec4(color, 1.0) * texture(image, tex);
}