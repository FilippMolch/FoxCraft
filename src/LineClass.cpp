#include "LineClass.h"

LineClass::LineClass(size_t capacity) : capacity(capacity) {
	buffer = new float[capacity * 7];
	index = 0;

	glLineWidth(2.5f);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 7 * capacity, buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(float) * 7, (void*)(sizeof(float) * 3));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LineClass::line(
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float r, float g, float b, float a)
{
	buffer[index + 0] = x1;
	buffer[index + 1] = y1;
	buffer[index + 2] = z1;

	buffer[index + 3] = r;
	buffer[index + 4] = g;
	buffer[index + 5] = b;
	buffer[index + 6] = a;

	index += 7;

	buffer[index + 0] = x2;
	buffer[index + 1] = y2;
	buffer[index + 2] = z2;

	buffer[index + 3] = r;
	buffer[index + 4] = g;
	buffer[index + 5] = b;
	buffer[index + 6] = a;

	index += 7;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 7 * capacity, buffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LineClass::clear(){
	for (size_t i = 0; i < index; i++)
		buffer[i] = 0;

	index = 0;

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 7 * capacity, buffer, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void LineClass::box(float x, float y, float z, float r, float g, float b, float a) {

	float offset  = 1.002;

	this->line(x, y + 0.001, z, x, y + offset, z, r, g, b, a);
	this->line(x, y + 0.001, z, x, y + 0.001, z + offset, r, g, b, a);
	this->line(x, y + 0.001, z, x + offset, y + 0.001, z, r, g, b, a);
	
	this->line(x, y + offset, z, x + offset, y + offset, z, r, g, b, a);
	this->line(x, y + offset, z, x, y + offset, z + offset, r, g, b, a);
	this->line(x + offset, y, z, x + offset, y + offset, z, r, g, b, a);
	
	this->line(x + offset, y + 0.001, z, x + offset, y + 0.001, z + offset, r, g, b, a);
	this->line(x, y + 0.001, z + offset, x + offset, y + 0.001, z + offset, r, g, b, a);
	this->line(x , y + 0.001, z + offset, x, y + offset, z + offset, r, g, b, a);
	
	this->line(x + offset, y + offset, z + offset, x, y + offset, z + offset, r, g, b, a);
	this->line(x + offset, y + 0.001, z + offset, x + offset, y + offset, z + offset, r, g, b, a);
	this->line(x + offset, y + offset, z, x + offset, y + offset, z + offset, r, g, b, a);

	this->draw();
	this->clear();

}

void LineClass::draw() {
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, index / 7);
	glBindVertexArray(0);
}