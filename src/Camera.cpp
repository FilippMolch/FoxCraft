#include "Camera.h"

using namespace std;

Camera::Camera(glm::vec3 Position, glm::vec3 Front, glm::vec3 Up){
	this->Position = Position;
	this->Front = Front;
	this->Up = Up;
    this->WorldUp = Up;

    updateVectors();
}

void Camera::updateVectors(){
    glm::vec3 direction;
    direction.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    direction.y = sin(glm::radians(this->pitch));
    direction.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
    this->Front = glm::normalize(direction);
    this->Right = glm::normalize(glm::cross(Front, WorldUp));  // Нормализуем векторы, потому что их длина становится стремится к 0 тем больше, чем больше вы смотрите вверх или вниз, что приводит к более медленному движению.
    this->Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::mouseCallBack(GLFWwindow* window, double xpos, double ypos){

    if (this->firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - this->lastX;
    float yoffset = this->lastY - ypos;
    this->lastX = xpos;
    this->lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    this->yaw += xoffset;
    this->pitch += yoffset;

    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    this->updateVectors();

}

void Camera::keyboardCallBack(GLFWwindow* win){
 
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    glm::vec3 Front2 = Front;
    if (Front.x < 0)
        Front2.x = -1.0f;
    if (Front.x > 0)
        Front2.x = 1.0f;

    CAM_SPEED = 2.5f * deltaTime;
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        CAM_SPEED = 10.0f * deltaTime;
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT) != GLFW_PRESS)
        CAM_SPEED = 2.5 * deltaTime;
    if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS)  
        Position += Front * CAM_SPEED;
    if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS)
        Position -= glm::normalize(Front) * CAM_SPEED;
    if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS)
        Position -= glm::normalize(glm::cross(Front, Up)) * CAM_SPEED;
    if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS)
        Position += glm::normalize(glm::cross(Front, Up)) * CAM_SPEED;

   // Position.y = 255.f;
}

glm::mat4 Camera::getLookAt(bool trig){
    if (!trig)
        return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
    else
        return glm::lookAt(glm::vec3(0.0f), this->Front, this->Up);
}

glm::mat4 Camera::getProj(unsigned int width, unsigned int height){
    float aspect = (float)width / (float)height;
    return glm::perspective(glm::radians(FOV), aspect, 0.1f, 1000.0f);
    //return glm::ortho(0.0f, 1020.0f, 10.0f, 720.0f, 0.1f, 100.0f);
}