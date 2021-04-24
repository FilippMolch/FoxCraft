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

void Camera::keyboardCallBack(Event& eve){
 
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    for (int i = 0; i < eve.keyboard.buttons.size(); i++)
    {
        switch (eve.keyboard.buttons[i])
        {
        case KEY_W:
            Position += Front * CAM_SPEED;
            break;
        case KEY_A:
            Position -= glm::normalize(glm::cross(Front, Up)) * CAM_SPEED;
            break;
        case KEY_S:
            Position -= glm::normalize(Front) * CAM_SPEED;
            break;
        case KEY_D:
            Position += glm::normalize(glm::cross(Front, Up)) * CAM_SPEED;
            break;

        default:
            break;
        }

        if (eve.keyboard.buttons[i] == KEY_LEFT_CONTROL)
            CAM_SPEED = 9.5 * deltaTime;
        else
            CAM_SPEED = 5.5 * deltaTime;
    }

    //CAM_SPEED = 2.5 * deltaTime;


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