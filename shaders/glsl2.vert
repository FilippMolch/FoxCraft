#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 vTexCoord;
out vec3 vNormal;
out vec3 FragPos;

uniform mat4 projView;
uniform mat4 model;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0));
	vNormal = aNormal;
	vTexCoord = aTexCoord;
	gl_Position = projView * model * vec4(aPos, 1.0f);
}