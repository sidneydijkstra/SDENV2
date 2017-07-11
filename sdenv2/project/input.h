
#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(GLFWwindow* _glfwWindow);
	~Input();

	// input functions
	float getMouseX();
	float getMouseY();
	bool getKey(int _keycode);
	bool getKeyDown(int _keycode);
private:
	// window
	GLFWwindow* _window;
}; 

#endif /* end input */