#version 460 core

in vec3 v_color;
in vec2 v_textcoord;

out vec4 f_color;

uniform float u_time;
uniform sampler2D u_texture;

void main()
{
	//f_Color = vec4(1.0, 0.5, 0.0, 0.0); // orange color
	//float offset  =  (sin(tan(u_time + (gl_FragCoord.x - gl_FragCoord.y))) * u_time);
	//f_color = vec4(v_color, 1.0); // Use vertex color

	f_color = texture(u_texture, v_textcoord) * vec4(v_color, 1);
}