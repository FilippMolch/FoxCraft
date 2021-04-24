#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec4 v_light;

out vec4 a_color;
out vec2 a_texCoord;


out vec2 vTexCoord;
out vec3 vNormal;
out vec3 FragPos;
out vec4 cord;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	a_color = vec4(v_light.r,v_light.g,v_light.b,1.0f);
	a_color.rgb += v_light.a;
	vTexCoord = aTexCoord;
	gl_Position = projView * model * vec4(aPos, 1.0f);
	cord = gl_Position;
}