#version 460 core

in vec3 v_Color;
out vec4 f_Color;
uniform float u_time;

void main()
{
	//f_Color = vec4(1.0, 0.5, 0.0, 0.0); // orange color
	float offset  =  (sin(tan(u_time + (gl_FragCoord.x - gl_FragCoord.y))) * u_time);
	f_Color = vec4(v_Color * offset , 1.0); // Use vertex color
}