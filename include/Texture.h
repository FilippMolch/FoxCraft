#pragma once

#ifndef TEXTURECLASS
#define TEXTURECLASS

#include <all.h>
#include <string>

using namespace std;

enum TextureType {
	TEXTURE_RGB,
	TEXTURE_RGBA
};

class TextureClass
{
private:
	int width, height, nrChannels;

	unsigned char* data;
	unsigned int texture;
public:
	
	TextureClass(string name, TextureType type);
	~TextureClass();

	static unsigned int loadCubemap(vector<std::string> faces);

	void bind();

};

#endif // !TEXTURECLASS