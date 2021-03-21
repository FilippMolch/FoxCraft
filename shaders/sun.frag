#version 450 core

in vec2 vTexCoord;
in vec3 vNormal;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
	FragColor = texture(tex, vTexCoord);
} 