#include "Mash.h"
#include <stb-master\stb_image.h>

Mesh::Mesh(vector<Vertex> vercites, vector<unsigned int> indices){
	this->vercites = vercites;
	this->indices = indices; 

	//this->setup();

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vercites.size() * sizeof(Vertex), &vercites[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
		&indices[0], GL_STATIC_DRAW);

	// Координаты вершин
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Нормали вершин
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	// Текстурные координаты вершин
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}
 
Mesh::Mesh(const float* buffer, size_t vertices, const int* attrs) : vertices(vertices) {
	int vertex_size = 0;
	for (int i = 0; attrs[i]; i++) {
		vertex_size += attrs[i];
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 0; attrs[i]; i++) {
		int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

Mesh::Mesh(vector<Vertex> vercites, vector<unsigned int> indices, vector<texture> textures) {
	this->vercites = vercites;
	this->indices = indices;
	this->t = textures;

	//this->setup();
}


vector<Vertex> Mesh::vectorVercitesAndTexCoordsToMash(vector<float> vertices, vector<float> TexCoords){
	Vertex v1;
	vector<Vertex> vert, vert2;

	for (int i = 0; i < (vertices.size()); i += 3)
	{
		v1.Position.x = vertices[i];
		v1.Position.y = vertices[i + 1];
		v1.Position.z = vertices[i + 2];

		vert.push_back(v1);
	}

	for (int i = 0; i < (TexCoords.size()); i += 2)
	{
		v1.TexCoords.x = TexCoords[i];
		v1.TexCoords.y = TexCoords[i + 1];

		vert2.push_back(v1);
	}


	for (int i = 0; i < vert.size(); i++)
	{
		if (i >= vert2.size())
			break;
		vert[i].TexCoords.x = vert2[i].TexCoords.x;
		vert[i].TexCoords.y = vert2[i].TexCoords.y;
	}

	return vert;
}

vector<unsigned int> Mesh::getIndices(vector<float> vertices){
	vector<unsigned int> ind;

	for (int i = 0; i < (vertices.size()); i++)
	{
		ind.push_back(i);
	}

	return ind;
}

void Mesh::draw(){
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

void Mesh::draw2(unsigned int primitive) {

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glDrawArrays(primitive, 0, vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}