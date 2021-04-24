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
	
	size_t capacity;
	
public:
	float* buffer;	

	Mesh* render(Chunk* chunk, const Chunk** chunks);
	RenderChunk(size_t capacity);
	~RenderChunk();
};

#endif // !RENDERCHUNKCLASS
