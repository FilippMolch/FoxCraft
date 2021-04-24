#pragma once

#ifndef FRAMEBUFFERCLASS
#define FRAMEBUFFERCLASS

#include <all.h>

using namespace std;

class FrameBuffer
{
private:
	unsigned int texture;
	unsigned int quadVAO, quadVBO;
	unsigned int hdrFBO;
	unsigned int rboDepth;
	unsigned int x, y;

public:
	FrameBuffer(unsigned int sizeX, unsigned int sizeY);
	void bindColorBuffer(bool trigg, GLFWwindow* window);
	void bindFrameBuffer(bool trigg);
	void bindColorBuffer(bool trigg);
	void renderCuadForColorBuffer();
};

#endif // !FRAMEBUFFERCLASS
