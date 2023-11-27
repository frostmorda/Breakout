#version 460
layout (location = 0) in vec2 vertex;
layout (location = 1) in vec2 tex_coords;
out vec2 tex;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    tex = tex_coords;
    gl_Position = projection * model * vec4(vertex, 0.0, 1.0);
}
