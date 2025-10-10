#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_color;
//layout (location = 2) in vec2 uv;

float frequency = 3.0;
float amplitude = 0.3;
out vec3 v_Color;
uniform float u_time;

void main()
{
	float frequency = 3.0;
	float amplitude = 0.3;
	vec3 position = a_position;

	float offset = sin(u_time * frequency + position.y) * amplitude;
	position.x += offset;


	v_Color = a_color;
	gl_Position = vec4(position * tan(u_time), 1.0);
}