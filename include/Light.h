#pragma once

#include <all.h>
#include <Chunks.h>

using namespace std;

#ifndef LIGHT
#define LIGHT

struct lightentry {
	int x;
	int y;
	int z;
	unsigned char light;
};

class Light
{
private:
	queue<lightentry> addqueue;
	queue<lightentry> remqueue;
	Chunks* chunks;
	int channel;
public:
	Light(Chunks* chunks, int channel);

	void add(int x, int y, int z);
	void add(int x, int y, int z, int emission);
	void remove(int x, int y, int z);
	void solve();
};


#endif // !LIGHTMAP