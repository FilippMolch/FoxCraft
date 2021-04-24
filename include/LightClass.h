#pragma once
#include <all.h>
#include <Chunks.h>
#include <Light.h>
#include <ChunkLightMap.h>
#include <Block.h>


#ifndef LIGHTLAAASSS
#define LIGHTLAAASSS

using namespace std;

class LightAll{
private:
	static Chunks* chunks;
	static Light* solverR;
	static Light* solverG;
	static Light* solverB;
	static Light* solverS;
public:

	static void init(Chunks* chunksInit);
	static void clear();
	static void WorldLoad();
	static void onBlockSet(int x, int y, int z, int id);

};
#endif // !LIGHTLAAASSS