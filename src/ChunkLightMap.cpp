#include "ChunkLightMap.h"

ChunkLightMap::ChunkLightMap(){
	map = new unsigned short[CHUNKV];

	for (int i = 0; i < CHUNKV; i++)
		map[i] = 0x0000;

}