#version 460 core

#define MAX_LIGHTS	5
#define DIRECTIONAL 0
#define POINT		1
#define SPOT		2

#define BASE_MAP			(1 << 0)
#define SPECULAR_MAP		(1 << 1)
#define EMISSIVE_MAP		(1 << 2)

in VS_OUT
{
	vec2 texcoord;
	vec3 position;
	vec3 normal;
} fs_in;

uniform int u_numLights = 3;

out vec4 f_color;

//uniform sampler2D u_texture;
uniform vec3 u_ambientLight;

uniform struct Material
{

	vec3 baseColor;
	vec3 emissiveColor;

	float shininess;
	vec2 tiling;
	vec2 offset;

	uint parameters;
}u_material;

uniform sampler2D u_baseMap;
uniform sampler2D u_specularMap;
uniform sampler2D u_emissiveMap;

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

float calculateAttenuation(in float lightDistance, in float range)
{
	float attenuation = max(0.0 ,(1.0 - (lightDistance / range)));
	return attenuation * attenuation;
}

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

	//float specularMask = 
	vec4 emissive = ((u_material.parameters & EMISSIVE_MAP) != 0u) 
	? texture(u_emissiveMap, fs_in.texcoord) * vec4(u_material.emissiveColor, 1)
	: vec4(u_material.emissiveColor, 1);

	vec3 color = u_ambientLight;
	for(int i = 0; i < u_numLights; i++)
	{
		color += calculateLight(u_lights[i], fs_in.position, fs_in.normal);
	}

	f_color = texture(u_baseMap, fs_in.texcoord) * vec4(color, 1);
	//f_color = vec4(v_normal, 1);
}