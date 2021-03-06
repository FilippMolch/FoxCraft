#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;


out vec4 vColor;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	vColor = aColor;
	gl_Position = projView * vec4(aPos, 1.0f);
}