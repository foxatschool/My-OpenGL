#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 2) in vec3 a_normal;

out vec3 v_texcoord;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform float u_ior;

void main()
{
	//Transform Position and Normal to World Space
	vec3 position = vec3(u_model * vec4(a_position, 1));
	vec3 normal = normalize(mat3(u_model) * a_normal);

	vec3 viewPosition = inverse(u_view)[3].xyz;
	vec3 viewDir = normalize(position - viewPosition);

	v_texcoord = refract(viewDir, normal, 1.0 / u_ior);

	//Remove Translation of Camera
	mat4 vp = u_projection * u_view * u_model;
	gl_Position = vp * vec4(a_position, 1.0);
}
