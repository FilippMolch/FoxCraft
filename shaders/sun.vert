#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoord;


out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	vTexCoord = aTexCoord;
	gl_Position = projView * model * vec4(aPos, 1.0f);
}