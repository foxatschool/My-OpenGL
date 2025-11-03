#version 460 core

in vec2 v_texcoord;
in vec3 v_position;
in vec3 v_normal;

out vec4 f_color;

//uniform sampler2D u_texture;
uniform vec3 u_ambientLight;

uniform struct Material
{
	sampler2D baseMap;
	vec3 baseColor;

	float shininess;
	vec2 tiling;
	vec2 offset;
}u_material;

uniform struct Light
{
	vec3 position;
	vec3 color;
}u_light;


vec3 calculateLight(in vec3 mv_position, in vec3 normal)
{
	

	//Diffuse
	vec3 light_dir = normalize(u_light.position - mv_position);
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = u_light.color * u_material.baseColor * intensity;


	//specular
	//phong
	//vec3 reflection = reflect(-light_dir, normal);
	//vec3 view_dir = normalize(-mv_position);
	//intensity = max(dot(reflection, view_dir), 0);

	//blinn-phong
	vec3 view_dir = normalize(-mv_position);
	vec3 halfway_dir = normalize(light_dir * view_dir);
	intensity = pow(intensity, u_material.shininess);

	intensity = pow(intensity, u_material.shininess);
	vec3 specular = vec3(intensity);


	return u_ambientLight + diffuse + specular;
}

void main()
{
	vec3 color = calculateLight(v_position, v_normal);
	f_color = texture(u_material.baseMap, v_texcoord) * vec4(color, 1);
	//f_color = vec4(v_normal, 1);
}