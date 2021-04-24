#include <iostream>

#include <all.h>

#include <Mash.h>
#include <Shader.h>
#include <RenderChunk.h>
#include <Chunk.h>
#include <Chunks.h>
#include <Coords.h>
#include <Camera.h>
#include <Window.h>
#include <Texture.h>
#include <RendererText.h>
#include <LightClass.h>
#include <cstdlib>
#include <FrameBuffer.h>
#include <PerlinNoiseInVector.h>
#include <LineClass.h>
#include <Light.h>
#include <Block.h>

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb-master/stb_image_write.h>

glm::vec3 cameraPos = glm::vec3(8.0f, 131.0f, 8.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.1f, 0.1f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

Shader shader("shaders/skybox.frag", "shaders/skybox.vert");
Shader shader2("shaders/chunk.frag", "shaders/chunk.vert");
Shader colorBuff("shaders/framebuffer.frag", "shaders/framebuffer.vert");
Shader cursorShader("shaders\\interface.frag", "shaders\\interface.vert");
Shader LineShader("shaders\\line.frag", "shaders\\line.vert");

Camera cam(cameraPos, cameraFront, cameraUp);

string camCoords = "PlayerCoords X: " + to_string(int(floor(cam.Position.x)))
							 + " Y: " + to_string(int(floor(cam.Position.y)))
							 + " Z: " + to_string(int(floor(cam.Position.z)));

string frontCoords = "Front X: " + to_string(cam.Front.x)
						+ " Y: " + to_string(cam.Front.y)
						+ " Z: " + to_string(cam.Front.z);

string upCoords = "Up X: " + to_string(cam.Up.x)
   				  + " Y: " + to_string(cam.Up.y)
				  + " Z: " + to_string(cam.Up.z);

string fpsSTR = "";

vector<string> faces = {
		"textures\\skybox\\right.jpg",
		"textures\\skybox\\left.jpg",
		"textures\\skybox\\top.jpg",
		"textures\\skybox\\bottom.jpg",
		"textures\\skybox\\front.jpg",
		"textures\\skybox\\back.jpg"
};


float width, height;

bool canMove = true;
bool canMove2 = true;

int lastTime = 0;
int nbFrames = 0;

double lastTim = glfwGetTime();

void screenShot(Window* window){
	if (glfwGetKey(window->window, GLFW_KEY_F1) == GLFW_PRESS) {

		unsigned char* pixels = new unsigned char[1920 * 1080 * 4];

		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		stbi_flip_vertically_on_write(1);
		auto now = std::chrono::system_clock::now();
		auto in_time_t = std::chrono::system_clock::to_time_t(now);

		string timeName = "screenshots\\" + to_string(in_time_t) + ".png";

		stbi_write_png(timeName.c_str(), width, height, 4, pixels, width * 4);

	}
}


void mouse(Window &window, voxel* vox, glm::vec3 end, glm::vec3 norm, glm::vec3 iend, Chunks* chunks){
	if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && canMove)
	{
		canMove = false;

		int x = (int)(iend.x) + (int)(norm.x);
		int y = (int)(iend.y) + (int)(norm.y);
		int z = (int)(iend.z) + (int)(norm.z);
		if (vox != nullptr)
			if (vox->id){
				chunks->set(x, y, z, Block::blocks[4]->id);
				LightAll::onBlockSet(x, y, z, Block::blocks[4]->id);
			}
	}
	else if (!canMove && glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		canMove = true;
	}

	if (glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && canMove2)
	{
		canMove2 = false;
		if (vox != nullptr){
			chunks->set((int)iend.x, (int)iend.y, (int)iend.z, 0);
			LightAll::onBlockSet((int)iend.x, (int)iend.y, (int)iend.z, Block::blocks[0]->id);
		}
		
	}
	else if (!canMove2 && glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		canMove2 = true;
	}
	else if (!canMove2 && glfwGetMouseButton(window.window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && glfwGetTime() * 1000 - lastTime > 5000)
	{
		lastTime = glfwGetTime() * 1000;
		canMove2 = true;
		
	}
}

int main(){
	width = 1920;
	height = 1080;

	Window window(width, height, "FoxCraft", false);

	window.mouseOnOff();

	shader.compile();
	shader2.compile();
	colorBuff.compile();
	cursorShader.compile();
	LineShader.compile();

	Chunks* chunks;
	chunks = new Chunks(10, 1, 10);
	Mesh** meshes = new Mesh * [chunks->volume];
	for (size_t i = 0; i < chunks->volume; i++)
		meshes[i] = nullptr;
	RenderChunk renderer(1024 * 1024 * 8);

	Mesh cubeMesh(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForCube, coords::verticesForCube), Mesh::getIndices(coords::verticesForCube));
	Mesh cur(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForRect, coords::rectTexCoords), coords::indecForRect);

	//Mesh cur(Mesh::vectorVercitesAndTexCoordsToMash(coords::verticesForCube, coords::verticesForCube), Mesh::getIndices(coords::verticesForCube));

	TextureClass tex("textures\\blocks\\block.png", TEXTURE_RGB, true);
	TextureClass cursorTex("textures\\blocks\\cursor.png", TEXTURE_RGBA, false);

	unsigned int cube = TextureClass::loadCubemap(faces);

	glm::mat4 curModel(1.0f);
	glm::mat4 sunModel(1.0f);
	glm::mat4 model(1.0f);

	model = glm::scale(model, glm::vec3(1000.f, 1000.f, 1000.f));

	RendererText text("fonts\\main.ttf"); 

	sunModel = glm::scale(sunModel, glm::vec3(30.f, 30.f, 0.f));
	sunModel = glm::translate(sunModel, glm::vec3(1.f, 1.f, 0.f));

	curModel = glm::translate(curModel, glm::vec3(100.0f, 100.0f, -10.0f));

	FrameBuffer fb(width, height);

	glm::mat4 lineModel(1.0f);
	LineClass line(100);

	Block* plank = new Block(4, 4);
	plank->emission[0] = 15;
	plank->emission[1] = 15;
	plank->emission[2] = 15;
	Block::blocks[plank->id] = plank;

	Block* dirt = new Block(2, 3);
	Block::blocks[dirt->id] = dirt;

	Block* grass = new Block(2, 2);
	grass->texture[0] = 1;
	grass->texture[1] = 1;
	grass->texture[2] = 2;
	grass->texture[3] = 3;
	grass->texture[4] = 1;
	grass->texture[5] = 1;
	Block::blocks[grass->id] = grass;

	Block* air = new Block(0, 0);
	air->DrGroup = 1;
	air->lightPassing = true;
	Block::blocks[air->id] = air;
	LightAll::init(chunks);
	LightAll::WorldLoad();

	while (!window.windowShouldClose())
	{
	
		glClearColor(1.0f,1.0f, 0.0f, 1.0f);
		fb.bindFrameBuffer(true);

			int time = clock();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_CUBE_MAP, cube);

			shader.use();
			shader.setMat4("projView", cam.getProj(width, height)*cam.getLookAt(true));
			shader.setMat4("model", model);
		
			cubeMesh.draw();

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			Chunk* closes[27];
			for (size_t i = 0; i < chunks->volume; i++) {
				Chunk* chunk = chunks->chunks[i];
				if (!chunk->modified)
					continue;
				chunk->modified = false;
				if (meshes[i] != nullptr)
					delete meshes[i];

				for (int i = 0; i < 27; i++)
					closes[i] = nullptr;
				for (size_t j = 0; j < chunks->volume; j++) {
					Chunk* other = chunks->chunks[j];

					int ox = other->x - chunk->x;
					int oy = other->y - chunk->y;
					int oz = other->z - chunk->z;

					if (abs(ox) > 1 || abs(oy) > 1 || abs(oz) > 1)
						continue;

					ox += 1;
					oy += 1;
					oz += 1;
					closes[(oy * 3 + oz) * 3 + ox] = other;
				}
				Mesh* mesh = renderer.render(chunk, (const Chunk**)closes);
				meshes[i] = mesh;
			}

			//ChunkRender(meshes, chunks, renderer);

			shader2.use();
			shader2.setMat4("projView", cam.getProj(width, height) * cam.getLookAt(false));
			tex.bind();
			glm::mat4 cunckModel;
			for (size_t i = 0; i < chunks->volume; i++) {
				Chunk* chunk = chunks->chunks[i];
				Mesh* mesh = meshes[i];
				cunckModel = glm::translate(mat4(1.0f), vec3(chunk->x * CHUNKSIZE_W + 0.5f, chunk->y * CHUNKSIZE_H + 0.5f, chunk->z * CHUNKSIZE_D + 0.5f));
				shader2.setMat4("model", cunckModel);
				meshes[i]->draw2(GL_TRIANGLES);
			}

			string camCoords = "PlayerCoords X: " + to_string(int(floor(cam.Position.x)))
										 + " Y: " + to_string(int(floor(cam.Position.y))) 
				       					 + " Z: " + to_string(int(floor(cam.Position.z)));

			string frontCoords = "Front X: " + to_string(cam.Front.x)
									+ " Y: " + to_string(cam.Front.y)
									+ " Z: " + to_string(cam.Front.z);

			string upCoords = "Up X: " + to_string(cam.Up.x)
							  + " Y: " + to_string(cam.Up.y)
							  + " Z: " + to_string(cam.Up.z);


			text.draw(camCoords, 15.0f, height - 15.0f - 15.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f), width, height);
			text.draw(frontCoords, 15.0f, height - 15.0f - 45.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f), width, height);
			text.draw(upCoords, 15.0f, height - 15.0f - 75.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f), width, height);

			string fps = "FPS: " + fpsSTR;

			double currentTime = glfwGetTime();
			nbFrames++;
			if (currentTime - lastTim >= 1.0) { 

				fpsSTR = to_string(double(nbFrames));

				nbFrames = 0;
				lastTim += 1.0;
			}

			text.draw(fps, 15.0f, height - 15.0f - 105.0f, 1.0f, glm::vec3(1.0, 1.0f, 1.0f), width, height);

			glm::mat4 project = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
			cursorShader.use();
			cursorShader.setMat4("proj", project);
			cursorShader.setMat4("model", curModel);
			cursorTex.bind();
			cur.draw();


			Event eve;
			window.PollEvents(eve);
			cam.keyboardCallBack(eve);
		
			vec3 end;
			vec3 norm;
			vec3 iend;
			voxel* vox = chunks->rayCast(cam.Position, cam.Front, 5.0f, end, norm, iend);

			LineShader.use();
			LineShader.setMat4("projView", cam.getProj(width, height) * cam.getLookAt(false));
			LineShader.setMat4("model", lineModel);
			
			if (vox != nullptr) {
				if (vox->id > 0)
					line.box(iend.x - 0.001, iend.y - 0.001, iend.z - 0.001, 0.0f, 0.0f, 0.0f, 0.6f);
			}

			mouse(window, vox, end, norm, iend, chunks);
			cam.mouseCallBack(window.window, eve.mouse.x, eve.mouse.y);

		fb.bindFrameBuffer(false);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

		fb.bindColorBuffer(true, window.window);

			colorBuff.use();
			colorBuff.setBool("hdr", true);
			colorBuff.setFloat("exposure", 0.45f);
			fb.renderCuadForColorBuffer();

			screenShot(&window);
			
		fb.bindColorBuffer(false);
	}
	
	glfwTerminate();
	return 0;
}

