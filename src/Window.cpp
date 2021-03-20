#include "Window.h"
#include <all.h>

Window::Window(unsigned int width, unsigned int height, string name, bool resizable){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

	FT_Library ft;

	// Всякий раз, когда возникает ошибка, функции будут возвращать отличное от нуля значение
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	}

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