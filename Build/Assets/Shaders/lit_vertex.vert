#version 460 core

#define MAX_LIGHTS	5
#define DIRECTIONAL 0
#define POINT		1
#define SPOT		2

layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;

out VS_OUT
{
	vec2 texcoord;
	vec3 color;
} vs_out;


uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_ambientLight;

uniform int u_numLights = 5;

uniform struct Light
{
	int type;
	vec3 position;
	vec3 color;
	vec3 direction;
	float intensity;
	float range;
	float outerSpotAngle;
	float innerSpotAngle;

} u_lights[MAX_LIGHTS];

uniform struct Material
{
	sampler2D baseMap;
	vec3 baseColor;

	float shininess;
	vec2 tiling;
	vec2 offset;
} u_material;

float calculateAttenuation(in float lightDistance, in float range)
{
	float attenuation = max(0.0 ,(1.0 - (lightDistance / range)));
	return attenuation * attenuation;
}

//uniform vec3 u_lightPos;
//diffuse
vec3 calculateLight(in Light light, in vec3 mv_position, in vec3 normal)
{
	float attenuation = 1.0;
	float lightDistance;
	vec3 light_dir;

	switch (light.type)
	{
		case DIRECTIONAL:
			light_dir = light.direction;
			//light_dir = vec3(0, 1, 0);//normalize(light.position - mv_position);
			break;

		case POINT:
			light_dir = normalize(light.position - mv_position);
			lightDistance = distance(light.position, mv_position);
			attenuation = calculateAttenuation(lightDistance, light.range);
			break;

		case SPOT:
			light_dir = normalize(light.position - mv_position);
		
			// spotlight cone attenuation
			lightDistance = length(light.position - mv_position);
			attenuation = calculateAttenuation(lightDistance, light.range);

			float angle = acos(dot(light_dir, light.direction));
			if (angle > light.outerSpotAngle)	attenuation = 0.0;
			else 
			{
				attenuation *= smoothstep(light.outerSpotAngle + 0.01, light.innerSpotAngle, angle);
			}
			break;
	}

	//Diffuse
	float NdotL = max(dot(normal, light_dir), 0);
	vec3 diffuse = light.color * u_material.baseColor * NdotL;



	//specular
	//vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-mv_position);
	//float RdotV = max(dot(reflection, view_dir), 0);
	//RdotV = pow(RdotV, u_material.shininess);
	//vec3 specular = vec3(RdotV);

	//blinn phong
	vec3 halfwayDir = normalize(light_dir + view_dir);
	float NdotH = max(dot(normal, halfwayDir), 0.0);
	NdotH = pow(NdotH, u_material.shininess);
	vec3 specular = vec3(NdotH);
	

	return (diffuse + specular) * light.intensity * attenuation;
}

void main()
{
	vs_out.texcoord = a_texcoord * u_material.tiling + u_material.offset;

	mat4 modelView = u_view * u_model;
	vec3 mv_position = vec3(modelView * vec4(a_position, 1));
	vec3 normal = normalize(mat3(modelView) * a_normal);

	vs_out.color = u_ambientLight;
	for (int i = 0; i < u_numLights; i++)
	{
		vs_out.color += calculateLight(u_lights[i],mv_position, normal);
	}

	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
