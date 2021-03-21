#pragma once

#ifndef RENDERTEXTCLASS
#define RENDERTEXTCLASS

#include <all.h>
#include <Shader.h>

using namespace std;

struct Character {
    unsigned int TextureID; // ID текстуры глифа
    glm::ivec2 Size; // размер глифа
    glm::ivec2 Bearing; // смещение от линии шрифта до верхнего/левого угла глифа
    unsigned int Advance; // смещение до следующего глифа
};


class RendererText
{
private:
    Shader *s;

    string fontPath;
    
    unsigned int VAO, VBO;
    
    map<char, Character> Characters;
public:
    void draw(string text, float xText, float yText, float scale, glm::vec3 color, unsigned int width, unsigned int height);

    RendererText(string fontPath);
    ~RendererText();
};

#endif // !RENDERTEXTCLASS
