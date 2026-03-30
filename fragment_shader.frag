#version 330 core
in vec3 out_color;
out vec4 color;
// uniform vec4 default_color;
in vec2 our_texture;

uniform sampler2D texture_sample1;

void main()
{
    color = vec4(out_color, 1.0f) * texture(texture_sample1, our_texture);
}
