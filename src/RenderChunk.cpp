#include "RenderChunk.h"

#define VERTEX_SIZE (3 + 2 + 1)

#define IS_IN(X,Y,Z) ((X) >= 0 && (X) < CHUNKSIZE_W && (Y) >= 0 && (Y) < CHUNKSIZE_H && (Z) >= 0 && (Z) < CHUNKSIZE_D)
#define VOXEL(X,Y,Z) (chunk->voxels[((Y) * CHUNKSIZE_D + (Z)) * CHUNKSIZE_W + (X)])
#define IS_BLOCKED(X,Y,Z) ((IS_IN(X, Y, Z)) && VOXEL(X, Y, Z).id)

#define VERTEX(INDEX, X,Y,Z, U,V, L) buffer[INDEX+0] = (X);\
								  buffer[INDEX+1] = (Y);\
								  buffer[INDEX+2] = (Z);\
								  buffer[INDEX+3] = (U);\
								  buffer[INDEX+4] = (V);\
								  buffer[INDEX+5] = (L);\
								  INDEX += VERTEX_SIZE;

int chunk_attrs[] = { 3,2,1, 0 };

Mesh* RenderChunk::render(Chunk* chunk){
	size_t index = 0;
	for (int y = 0; y < CHUNKSIZE_H; y++)
	{
		for (int z = 0; z < CHUNKSIZE_D; z++)
		{
			for (int x = 0; x < CHUNKSIZE_W; x++)
			{
				voxel vox = chunk->voxels[(y * CHUNKSIZE_D + z) * CHUNKSIZE_W + x];
				unsigned int id = vox.id;

				if (!id) {
					continue;
				}

				float l;
				float uvsize = 1.0f / 16.0f;
				float u = (id % 16) * uvsize;
				float v = 1 - ((1 + id / 16) * uvsize);

				if (!IS_BLOCKED(x, y + 1, z)) {
					l = 1.0f;
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 0.0f, 0.0f, l);
				}
				if (!IS_BLOCKED(x, y - 1, z)) {
					l = 0.75f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, l);
				}

				if (!IS_BLOCKED(x + 1, y, z)) {
					l = 0.95f;
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, l);
				}
				if (!IS_BLOCKED(x - 1, y, z)) {
					l = 0.85f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 0.0f, 0.0f, l);
				}

				if (!IS_BLOCKED(x, y, z + 1)) {
					l = 0.9f;
					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z + 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z + 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z + 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z + 0.5f, 0.0f, 0.0f, l);
				}
				if (!IS_BLOCKED(x, y, z - 1)) {
					l = 0.8f;
					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, l);
					VERTEX(index, x - 0.5f, y + 0.5f, z - 0.5f, 1.0f, 0.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 1.0f, 1.0f, l);

					VERTEX(index, x - 0.5f, y - 0.5f, z - 0.5f, 1.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y + 0.5f, z - 0.5f, 0.0f, 1.0f, l);
					VERTEX(index, x + 0.5f, y - 0.5f, z - 0.5f, 0.0f, 0.0f, l);
				}
			}
		}
	}
	return new Mesh(buffer, index / VERTEX_SIZE, chunk_attrs);
}

RenderChunk::RenderChunk(size_t capacity) {
	buffer = new float[capacity * VERTEX_SIZE * 6];
}

RenderChunk::~RenderChunk(){


}