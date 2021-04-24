#pragma once

#include <all.h>

using namespace std;

#ifndef BLOCK
#define BLOCK


class Block
{
public:
	static Block* blocks[256];

	unsigned char emission[3];
	unsigned char DrGroup;
	int texture[6];

	bool lightPassing = false;

	unsigned int id;

	Block(int texture, unsigned int id);
};

#endif 