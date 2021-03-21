#include "Window.h"
#include <all.h>

Window::Window(unsigned int width, unsigned int height, string name, bool resizable){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_DECORATED, 0);

	if (!resizable)
		glfwWindowHint(GLFW_RESIZABLE, NULL);

	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (window == NULL) {
		cerr << "WINDOW::CREATE:ERROR" << endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "Failed to initialize GLAD" << endl;
		glfwTerminate();
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}

void Window::PollEvents(){
	glfwPollEvents();
}

void Window::SwapBuffers(){
	glfwSwapBuffers(window);
}

void Window::mouseOnOff(){

	glfwSetInputMode(window, GLFW_CURSOR, mouseTrigg ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
	mouseTrigg = !mouseTrigg;

}

bool Window::windowShouldClose(){
	return glfwWindowShouldClose(window);
}

Window::~Window(){
	glfwTerminate();
}