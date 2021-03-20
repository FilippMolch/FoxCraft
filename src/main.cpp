#include <iostream>

#include <all.h>

#include <Mash.h>
#include <Shader.h>
#include <RenderChunk.h>
#include <Chunk.h>
#include <Coords.h>
#include <Camera.h>
#include <Window.h>
#include <Texture.h>

using namespace std;

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera cam(cameraPos, cameraFront, cameraUp);

unsigned int width, height;

void procInput(GLFWwindow* window){

	cam.keyboardCallBack(window);

}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	cam.mouseCallBack(window, xpos, ypos);
}

int main(){

	width = 1024;
	height = 720;

	Window window(width, height, "FoxCraft", false);

	window.mouseOnOff();
	glfwSetCursorPosCallback(window.window, mouse_callback);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("shaders/skybox.frag", "shaders/skybox.vert");
	shader.compile();

	Shader shader2("shaders/chunk.frag", "shaders/chunk.vert");
	shader2.compile();

	RenderChunk renderer(1024 * 1024 * 8);
	Chunk* chunk = new Chunk();
	Mesh* mesh = renderer.render(chunk);


	vector<string> faces = {
		"textures\\right.jpg",
		"textures\\left.jpg",
		"textures\\top.jpg",
		"textures\\bottom.jpg",
		"textures\\front.jpg",
		"textures\\back.jpg"
	};

	Mesh cubeMesh(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForCube, coords::verticesForCube), Mesh::getIndices(coords::verticesForCube));


	TextureClass tex("textures\\2.png", TEXTURE_RGBA);
	unsigned int cube = TextureClass::loadCubemap(faces);

	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(1000.f, 1000.f, 1000.f));

	while (!window.windowShouldClose())
	{
		procInput(window.window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f,1.0f, 0.0f, 1.0f);

		glBindTexture(GL_TEXTURE_CUBE_MAP, cube);

		shader.use();
		shader.setMat4("projView", cam.getProj(width, height)*cam.getLookAt(true));
		shader.setMat4("model", model);
		
		cubeMesh.draw();

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		shader2.use();
		shader2.setMat4("projView", cam.getProj(width, height) * cam.getLookAt(false));
		shader2.setMat4("model", glm::mat4(1.0f));
		tex.bind();
		mesh->draw2(GL_TRIANGLES);

		window.PollEvents();
		window.SwapBuffers();
	}

	glfwTerminate();
	return 0;
}
