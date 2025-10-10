#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;
//layout (location = 2) in vec2 uv;

out vec3 v_Color;
uniform float u_time;

void main()
{
	v_Color = a_color;
	gl_Position = vec4(a_position * tan(u_time), 1.0);
}