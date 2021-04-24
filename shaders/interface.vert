#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords; 

uniform mat4 proj;
uniform mat4 model;

void main()
{
    TexCoords = aTexCoords;
    //proj *
    gl_Position = proj * model * vec4(aPos.xy, 1.0f, 1.0);
}