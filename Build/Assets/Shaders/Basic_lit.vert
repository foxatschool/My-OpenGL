#version 460 core

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out vec2 v_texcoord;
flat out vec3 v_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_ambientLight;

uniform struct Light
{
	vec3 position;
	vec3 color;
}u_light;

uniform struct Material
{
	sampler2D baseMap;
	vec3 baseColor;

	float shininess;
	vec2 tiling;
	vec2 offset;
}u_material;



//uniform vec3 u_lightPos;
//diffuse
vec3 calculateLight(in vec3 mv_position, in vec3 normal)
{
	//Diffuse
	vec3 light_dir = normalize(u_light.position - mv_position);
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = u_light.color * u_material.baseColor * intensity;


	//specular
	vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-mv_position);
	intensity = max(dot(reflection, view_dir), 0);
	intensity = pow(intensity, u_material.shininess);
	vec3 specular = vec3(intensity);


	return u_ambientLight + diffuse + specular;
}

void main()
{
	v_texcoord = a_texcoord * u_material.tiling + u_material.offset;

	mat4 modelView = u_view * u_model;
	vec3 mv_position = vec3(modelView * vec4(a_position, 1));
	vec3 normal = normalize(mat3(modelView) * a_normal);

	v_color = calculateLight(mv_position, normal);

	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
