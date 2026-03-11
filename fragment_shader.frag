#version 330 core
in vec3 out_color;
out vec4 color;
//uniform vec4 default_color;

void main()
{
    // color=vertex_color;
    color=vec4(out_color, 1.0);
}
