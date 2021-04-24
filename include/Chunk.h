#pragma once

#ifndef CHUNKCLASS
#define CHUNKCLASS

#include <all.h>
#include <ChunkLightMap.h>

using namespace std;

#define CHUNKSIZE_W 16
#define CHUNKSIZE_H 255
#define CHUNKSIZE_D 16

struct voxel {
	unsigned int id;
};

class Chunk
{
private:
public:
	int x, y, z;
	voxel* voxels;

	ChunkLightMap* lightmap;

	bool modified = true;

	Chunk(int xpos, int ypos, int zpos);
	Chunk(int xpos, int ypos, int zpos, bool perlin);
	~Chunk();
};

#endif // !CHUNKCLASS