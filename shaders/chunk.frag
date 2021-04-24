#version 450 core

in vec2 vTexCoord;
out vec4 FragColor;
uniform sampler2D tex;
in vec4 a_color;

void main()
{
    FragColor = a_color * texture2D(tex, vTexCoord);
} 