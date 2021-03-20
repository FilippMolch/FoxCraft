#pragma once

#ifndef CHUNKCLASS
#define CHUNKCLASS

#include <all.h>

using namespace std;

#define CHUNKSIZE_W 16
#define CHUNKSIZE_H 255
#define CHUNKSIZE_D 16

struct voxel {
	uint8_t id;
};

class Chunk
{
private:
public:
	voxel* voxels = new voxel[CHUNKSIZE_W * CHUNKSIZE_H * CHUNKSIZE_D];

	Chunk();
	~Chunk();
};

#endif // !CHUNKCLASS