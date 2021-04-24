#include "Chunk.h"
#include <glm/gtc/noise.hpp>
#include <ChunkLightMap.h>

Chunk::Chunk(int xpos, int ypos, int zpos) : x(xpos), y(ypos), z(zpos) {
	voxels = new voxel[CHUNKSIZE_H * CHUNKSIZE_W * CHUNKSIZE_D];

	for (int y = 0; y < CHUNKSIZE_H; y++) {
		for (int z = 0; z < CHUNKSIZE_D; z++) {
			for (int x = 0; x < CHUNKSIZE_W; x++) {
				voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = 0;
			}
		}
	}

	for (int y = 0; y < CHUNKSIZE_H; y++) {
		for (int z = 0; z < CHUNKSIZE_D; z++) {
			for (int x = 0; x < CHUNKSIZE_W; x++) {
				int real_x = x + this->x * CHUNKSIZE_W;
				int real_y = y + this->y * CHUNKSIZE_H;
				int real_z = z + this->z * CHUNKSIZE_D;
				int id = real_y <= (sin(real_x * 0.1f) * 0.5f + 0.5f) * 10;
				if (real_y <= 2)
					id = 2;
				if (y < 100)
					voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = 1;
			}
		}
	}
};

Chunk::Chunk(int xpos, int ypos, int zpos, bool perlin) : x(xpos), y(ypos), z(zpos) {
	voxels = new voxel[CHUNKSIZE_H * CHUNKSIZE_W * CHUNKSIZE_D];
	lightmap = new ChunkLightMap();

	for (int y = 0; y < CHUNKSIZE_H; y++) {
		for (int z = 0; z < CHUNKSIZE_D; z++) {
			for (int x = 0; x < CHUNKSIZE_W; x++) {
				voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = 0;
			}
		}
	}

	for (int y = 0; y < CHUNKSIZE_H; y++) {
		for (int z = 0; z < CHUNKSIZE_D; z++) {
			for (int x = 0; x < CHUNKSIZE_W; x++) {
				int real_x = x + this->x * CHUNKSIZE_W;
				int real_y = y + this->y * CHUNKSIZE_H;
				int real_z = z + this->z * CHUNKSIZE_D;
				int i = 3;
				if (y > 89 && y < 110)
				{
					unsigned int height = ceil(glm::perlin(glm::vec2(real_z * 0.039f, real_x * 0.039f)) * 9);
					
	 				voxels[((y + height) * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = i;
				}

				if (y < 90){
				//, real_z * 0.0100f
					int id = glm::perlin(glm::vec3(real_x * 0.09f, real_y * 0.09f, real_z * 0.09f)) > -0.5 ? i : 0;
					voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = id;
				}
				
			}
		}
	}
};

Chunk::~Chunk(){
	delete[] voxels;
};	