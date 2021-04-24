#include "PerlinNoiseInVector.h"


PerlinNoiseInVector::PerlinNoiseInVector(unsigned int rectSize) : rectSize(rectSize) {

	myModule.SetSeed(235324534);

	heightMapBuilder.SetSourceModule(myModule);
	heightMapBuilder.SetDestNoiseMap(heightMap);
	heightMapBuilder.SetDestSize(rectSize, rectSize);
	heightMapBuilder.SetBounds(6.0, 10.0, 1.0, 5.0);
	heightMapBuilder.Build();
}

double** PerlinNoiseInVector::getVector(){
	double** cache = (double**)new double * [(rectSize / 16) * (rectSize / 16)];

	vector<double>* vectorCache = new vector<double>;
	vectorCache->clear();

	for (int i = 0; i < (rectSize / 16) * (rectSize / 16); i++)
		cache[i] = (double*)new double * [256];

	for (int clear = 0; clear < (rectSize / 16) * (rectSize / 16); clear++)
		for (int clear2 = 0; clear2 < 256; clear2++)
			cache[clear][clear2] = 0.0;

	unsigned int x = 0;
	unsigned int y = 0;

	for (int tile = 0; tile < (rectSize / 16) * (rectSize / 16); tile++)
	{

		for (unsigned int tileSizeY = 0; tileSizeY < 17; tileSizeY++){
			for (unsigned int tileSizeX = 0; tileSizeX < 17; tileSizeX++){	
				vectorCache->push_back(heightMap.GetValue(tileSizeX + x, tileSizeY + y));
			}
		}
		
		x += 16;
		if (x >= rectSize)
			y += 16;

		if (x >= rectSize && y >= rectSize)
			break;

		if (x >= rectSize)
			x = 0;

	}

	vector<double>::const_iterator it = vectorCache->begin();

	for (int i = 0; i < (rectSize / 16) * (rectSize / 16); i++)
	{
		
		for (int i2 = 0; i2 < 256; i2++)
		{
			cache[i][i2] = *it;
			++it;
		}

	}
	
	return cache;
}