

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
	static Input* getInstance();
	~Input();

	static void init(GLFWwindow * window);

	// input update
	static void update();

	// input functions
	static float getMouseX();
	static float getMouseY();
	static bool getKey(int _keycode);
	static bool getKeyDown(int _keycode);

	// event handelers
	static void _handleKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void _handleMouse(GLFWwindow* window, double xpos, double ypos);
	static void _handleScroll(GLFWwindow* window, double xoffset, double yoffset);

	// delete input
	static void delInput() { delete instance; };

private:
	Input();
	// instance of input
	static Input* instance;

	// window
	GLFWwindow* window;

	// key
	bool _keys[GLFW_KEY_LAST];
	bool _keysDown[GLFW_KEY_LAST];

	// mouse
	float _mouseX;
	float _mouseY;


}; 

#endif /* end input */