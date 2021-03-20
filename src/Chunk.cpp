#include "Chunk.h"

Chunk::Chunk(){
	for (int y = 0; y < CHUNKSIZE_H; y++)
	{
		for (int z = 0; z < CHUNKSIZE_D; z++)
		{
			for (int x = 0; x < CHUNKSIZE_W; x++)
			{
				
				int id = y <= (sin(x * 0.3f) * 0.5f + 0.5f) * 10;

				//cout << "X: " << x << " Y: " << y << " Z: " << z << endl;
				voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x].id = 1;

				
			}
		}
	}
};

Chunk::~Chunk(){
	delete[] voxels;
};	