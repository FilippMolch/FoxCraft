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
#include <RendererText.h>

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

	width = 1020;
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

	Shader sunShader("shaders\\sun.frag", "shaders\\sun.vert");
	sunShader.compile();

	RenderChunk renderer(1024 * 1024 * 8);
	Chunk* chunk = new Chunk();
	Mesh* mesh = renderer.render(chunk);


	vector<string> faces = {
		"textures\\skybox\\right.jpg",
		"textures\\skybox\\left.jpg",
		"textures\\skybox\\top.jpg",
		"textures\\skybox\\bottom.jpg",
		"textures\\skybox\\front.jpg",
		"textures\\skybox\\back.jpg"
	};

	Mesh cubeMesh(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForCube, coords::verticesForCube), Mesh::getIndices(coords::verticesForCube));
	
	Mesh sun(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForCube, coords::verticesForCube), Mesh::getIndices(coords::verticesForCube));


	TextureClass tex("textures\\blocks\\2.png", TEXTURE_RGBA);

	TextureClass sunTex("textures\\lights\\sun.png", TEXTURE_RGBA);

	unsigned int cube = TextureClass::loadCubemap(faces);

	glm::mat4 model(1.0f);
	model = glm::scale(model, glm::vec3(1000.f, 1000.f, 1000.f));

	RendererText text("fonts\\main.ttf");

	glm::mat4 sunModel(1.0f);
	sunModel = glm::scale(sunModel, glm::vec3(30.f, 30.f, 30.f));
	sunModel = glm::translate(sunModel, glm::vec3(17.f, 17.f, 0.f));

	while (!window.windowShouldClose())
	{
		procInput(window.window);


		//cam.Position.y = 255.f;

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
		
		sunShader.use();
		sunShader.setMat4("projView", cam.getProj(width, height) * cam.getLookAt(false));
		sunShader.setMat4("model", sunModel);
		sunTex.bind();
		sun.draw();

		string camCoords = "PlayerCoords X: " + to_string(int(floor(cam.Position.x)))
								     + " Y: " + to_string(int(floor(cam.Position.y))) 
				       				 + " Z: " + to_string(int(floor(cam.Position.z)));

		string frontCoords = "Front X: " + to_string(cam.Front.x)
							    + " Y: " + to_string(cam.Front.y)
							    + " Z: " + to_string(cam.Front.z);

		string upCoords = "Up X: " + to_string(cam.Up.x)
						  + " Y: " + to_string(cam.Up.y)
						  + " Z: " + to_string(cam.Up.z);


		text.draw(camCoords, 15.0f, 695.0f - 15.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
		text.draw(frontCoords, 15.0f, 695.0f - 45.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));
		text.draw(upCoords, 15.0f, 695.0f - 75.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f));

		window.PollEvents();
		window.SwapBuffers();
	}

	glfwTerminate();
	return 0;
}
