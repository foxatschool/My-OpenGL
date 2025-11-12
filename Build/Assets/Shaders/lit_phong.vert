#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out VS_OUT
{
	vec2 texcoord;
	vec3 position;
	vec3 normal;
} vs_out;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;


uniform struct Material
{
	vec3 baseColor;
	vec3 emissiveColor;

	float shininess;
	vec2 tiling;
	vec2 offset;

	uint parameters;
}u_material;

uniform sampler2D baseMap;
uniform vec3 u_lightPos;
uniform sampler2D u_specularMap;
//diffuse


void main()
{
	vs_out.texcoord = a_texcoord * u_material.tiling + u_material.offset;

	mat4 modelView = u_view * u_model;

	vs_out.position = vec3(modelView * vec4(a_position, 1));
	vs_out.normal = normalize(mat3(modelView) * a_normal);

	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
