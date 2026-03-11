#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec2 text_color;
out vec3 out_color;

void main()
{
	gl_Position=vec4(position, 1.0);
	out_color = in_color;
	// vertex_color=vec4(1.0f, 0.0f, 0.0f, 1.0f);
}
