#pragma once

#include <all.h>
#include <noise/noise.h>
#include <noiseutils.h>

using namespace std;
using namespace noise;

class PerlinNoiseInVector
{
private:
	module::Perlin myModule;

	utils::NoiseMap heightMap;
	utils::NoiseMapBuilderPlane heightMapBuilder;

	unsigned int rectSize;
public:
	PerlinNoiseInVector(unsigned int rectSize);

	double** getVector();
};

