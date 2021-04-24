#include <Shader.h>

Shader::Shader(){

}

Shader::Shader(string FragmentShaderPath, string VertexShaderPath){
	ifstream FragmentFile(FragmentShaderPath);
	ifstream VertexFile(VertexShaderPath);

	FragmentShaderStream << FragmentFile.rdbuf();
	VertexShaderStream   << VertexFile.rdbuf();

	FragmentFile.close();
	VertexFile.close();

	FragmentShaderSourceStr = FragmentShaderStream.str();
	VertexShaderSourceStr   = VertexShaderStream.str();
}

void Shader::compile(){
	
	const char* FragmentShaderSource = FragmentShaderSourceStr.c_str();
	const char* VertexShaderSource = VertexShaderSourceStr.c_str();

	Fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(Fragment, 1, &FragmentShaderSource, NULL);
	glCompileShader(Fragment);

	Vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(Vertex, 1, &VertexShaderSource, NULL);
	glCompileShader(Vertex);

	ID = glCreateProgram();
	glAttachShader(ID, Fragment);
	glAttachShader(ID, Vertex);
	glLinkProgram(ID);

    this->getCompileError();

    glDeleteShader(Vertex);
    glDeleteShader(Fragment);
}

void Shader::getCompileError(){
	int success;
	char infoLog[512];
	glGetShaderiv(Vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Vertex, 512, NULL, infoLog);
		cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	glGetShaderiv(Fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(Fragment, 512, NULL, infoLog);
		cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
}

void Shader::setFloat(string name, float value){
	unsigned int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1f(loc, value);
}

void Shader::setInt(string name, int value){
	unsigned int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(loc, value);
}

void Shader::setBool(string name, bool value){
	unsigned int loc = glGetUniformLocation(ID, name.c_str());
	glUniform1i(loc, (int)value);
}

void Shader::setMat4(string name, glm::mat4 matrix){
	unsigned int matLoc = glGetUniformLocation(ID, name.c_str());
	glUniformMatrix4fv(matLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::use(){
	glUseProgram(ID);
}

void Shader::deleteProgramm(){
	glDeleteProgram(ID);
}

Shader::~Shader(){
	//glDeleteProgram(ID);
}

void Shader::setVec3(string name, float value, float value2, float value3){
	unsigned int Loc = glGetUniformLocation(ID, name.c_str());
	glUniform3f(Loc, value, value2, value3);
}