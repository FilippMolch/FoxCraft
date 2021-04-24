#pragma once
#ifndef CHUNKSCLASS
#define CHUNKSCLASS

#include <all.h>
#include <Chunk.h>

using namespace std;
using namespace glm;

class Chunks
{
public:
	Chunk** chunks;
	size_t volume;
	unsigned int w, h, d;

	Chunks(int w, int h, int d);
	Chunks(int w, int h, int d, double** perlin);
	~Chunks();

	Chunk* getChunk(int x, int y, int z);
	voxel* get(int x, int y, int z);
	void set(int x, int y, int z, int id);
	voxel* rayCast(vec3 start, vec3 dir, float maxLength, vec3& end, vec3& norm, vec3& iend);
	Chunk* getChunkByVoxel(int x, int y, int z);
	unsigned char getLight(int x, int y, int z, int channel);
};

#endif // !CHUNKSCLASS
