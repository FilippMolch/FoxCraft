#pragma once

#include <all.h>

#ifndef LINECLASS
#define LINECLASS

using namespace std;

class LineClass
{
private:
	float* buffer;
	int index;
	size_t capacity;
	unsigned int VBO, VAO;
public:
	LineClass(size_t capacity);

	void line(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float r, float g, float b, float a
	);

	void box(float x, float y, float z, float r, float g, float b, float a);
	
	void clear();
	void draw();


};


#endif // !LINECLASS