#pragma once
#ifndef CAMERA
#define CAMERA

#include <all.h>
#include <Window.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	bool firstMouse;

	float yaw = 0;
	float pitch = 0;
	float lastX = 0;
	float lastY = 0;

	void updateVectors();

public:
	
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float FOV = 75.0f;
	float CAM_SPEED = 1.5f;

	Camera(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up);
	void mouseCallBack(GLFWwindow* window, double xpos, double ypos);
	void keyboardCallBack(Event& eve);

	glm::mat4 getLookAt(bool trig);
	glm::mat4 getProj(unsigned int width, unsigned int height);

};

#endif