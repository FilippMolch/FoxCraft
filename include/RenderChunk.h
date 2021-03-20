#pragma once

#ifndef RENDERCHUNKCLASS
#define RENDERCHUNKCLASS

#include <all.h>
#include <Chunk.h>
#include <Mash.h>

using namespace std;

class RenderChunk
{
private:
	float* buffer;
	size_t capacity;

public:
	Mesh* render(Chunk* chunk);
	RenderChunk(size_t capacity);
	~RenderChunk();
};

#endif // !RENDERCHUNKCLASS
