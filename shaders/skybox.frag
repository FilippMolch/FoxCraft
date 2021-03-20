#version 450 core

in vec3 vTexCoord;

out vec4 FragColor;

uniform samplerCube tex;

void main()
{
    FragColor = texture(tex, vTexCoord) - vec4(0.0f, 0.0f, 0.0f, 0.0f);// * vec4(result, 1.0f);
}