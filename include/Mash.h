#pragma once

#ifndef MASHCLASS

#define MASHCLASS

#include <all.h>
#include <Shader.h>

using namespace std;

struct texture {
	unsigned int id;
	string type;
	string path;
};

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

class Mesh
{
private:
	unsigned int VBO, VAO;
	unsigned int EBO;
	unsigned int tex;

	size_t vertices;

	string texName = "textures\\1.jpg";

	vector<Vertex> vercites; 
	vector<texture> t;
	vector<unsigned int> indices;

	//void setup();

public:
	void draw();
	void draw2(unsigned int primitive);

	static vector<Vertex> vectorVercitesAndTexCoordsToMash(vector<float> vertices, vector<float> TexCoords);
	static vector<unsigned int> getIndices(vector<float> vertices);


	Mesh(const float* buffer, size_t vertices, const int* attrs);
	Mesh(vector<Vertex> vercites, vector<unsigned int> indices);
	Mesh(vector<Vertex> vercites, vector<unsigned int> indices, vector<texture> textures);
};

#endif // !MASHCLASS
