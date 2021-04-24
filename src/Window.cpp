#include "Window.h"

Window::Window(unsigned int width, unsigned int height, string name, bool resizable){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_DECORATED, 0);
	glfwWindowHint(GL_MULTISAMPLE, 10);

	if (!resizable)
		glfwWindowHint(GLFW_RESIZABLE, NULL);

	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);

	if (window == NULL) {
		cerr << "WINDOW::CREATE:ERROR" << endl;
		glfwTerminate();
	}


	glfwMakeContextCurrent(window);
	//glfwSwapInterval(0);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cerr << "Failed to initialize GLAD" << endl;
		glfwTerminate();
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	//glEnable(GL_FRAMEBUFFER_SRGB);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void Window::PollEvents(Event& eve){
	
	glfwPollEvents();
	this->SwapBuffers();

	for (int i = 65; i != 91; i++)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS){
			eve.keyboard.buttons.push_back(i);
		}
	}

	for (int i = 256; i != 348; i++)
	{
		if (glfwGetKey(window, i) == GLFW_PRESS) {
			eve.keyboard.buttons.push_back(i);
		}
	}


	vector<int>::const_iterator it;
 	it = eve.keyboard.buttons.begin();
	for (int i = 0; i < eve.keyboard.buttons.size(); i++)
	{
		if (glfwGetKey(window, eve.keyboard.buttons[i]) != GLFW_PRESS)
			eve.keyboard.buttons.erase(it);
		it++;
	}

	glfwGetCursorPos(this->window, &x, &y);
	eve.mouse.x = this->x;
	eve.mouse.y = this->y;

	for (int i = 0; i != 2; i++)
	{
		if (glfwGetMouseButton(window, i) == GLFW_PRESS) {
			eve.mouse.buttons.push_back(i);
		}
	}

	vector<int>::const_iterator it2;
	it2 = eve.mouse.buttons.begin();
	for (int i = 0; i < eve.mouse.buttons.size(); i++)
	{
		if (glfwGetMouseButton(window, eve.mouse.buttons[i]) == GLFW_RELEASE){
			eve.mouse.buttons.erase(it2);
			//eve.mouse.unpressedButtons.push_back(eve.mouse.buttons[i]);
		}
		it2++;
	}
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