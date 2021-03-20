#pragma once


#ifndef WINDOWCLASS
#define WINDOWCLASS

#include <all.h>
#include <string>

using namespace std;

class Window
{
private:
	bool mouseTrigg = true;
public:
	GLFWwindow* window;

	void PollEvents();
	void SwapBuffers();
	void mouseOnOff();

	bool windowShouldClose();

	Window(unsigned int width, unsigned int height, string name, bool resizable);
	~Window();

};
#endif // !WINDOWCLASS