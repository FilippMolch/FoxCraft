#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
//layout (location = 1) in vec3 aColor;

out vec3 vTexCoord;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	vTexCoord = aPos;
	gl_Position = projView * model * vec4(aPos, 1.0f);
}