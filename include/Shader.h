#pragma once

#include <all.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#ifndef ShaderClass
#define ShaderClass

class Shader
{
private:
	unsigned int Fragment, Vertex;
	string FragmentShaderPath, VertexShaderPath;
	stringstream FragmentShaderStream, VertexShaderStream;
	string FragmentShaderSourceStr, VertexShaderSourceStr;
public:

	unsigned int ID;

	void compile();
	void use();
	void getCompileError();
	void deleteProgramm();
	void setFloat(string name, float value);
	void setInt(string name, int value);
	void setBool(string name, bool value);
	void setMat4(string name, glm::mat4 matrix);
	void setVec3(string name, float value, float value2, float value3);

	Shader(string FragmentShaderPath, string VertexShaderPath);
	Shader();
	~Shader();
};

#endif