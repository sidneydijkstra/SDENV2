#include "input.h"

// event handelers
void _handleKey(GLFWwindow* window, int key, int scancode, int action, int mode);
void _handleMouse(GLFWwindow* window, double xpos, double ypos);
void _handleScroll(GLFWwindow* window, double xoffset, double yoffset);

// key
bool _keys[GLFW_KEY_LAST];

// mouse
int _mouseX;
int _mouseY;

// input constructor
Input::Input(GLFWwindow* glfwWindow){
	// set window
	_window = glfwWindow;

	// Set the required callback functions
	glfwSetKeyCallback(_window, _handleKey);
	glfwSetCursorPosCallback(_window, _handleMouse);
	glfwSetScrollCallback(_window, _handleScroll);

	// set all key bools to false
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		_keys[i] = false;
	}

	// input create message
	//std::cout << "Input created!" << std::endl;
}

// get mouse x
float Input::getMouseX() {
	return _mouseX;
}

// get mouse y
float Input::getMouseY() {
	return _mouseY;
}

// get key press
bool Input::getKey(int keycode) {
	return _keys[keycode];
}

// key handeler
void _handleKey(GLFWwindow * window, int key, int scancode, int action, int mode){
	if (key >= 0 && key <= GLFW_KEY_LAST) {
		if (action == GLFW_PRESS) {
			_keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			_keys[key] = false;
		}
	}

	// exit on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

// mouse handeler
void _handleMouse(GLFWwindow * window, double xpos, double ypos){
	_mouseX = xpos;
	_mouseY = ypos;
}

// scroll handeler
void _handleScroll(GLFWwindow * window, double xoffset, double yoffset){
}

// input deconstructor
Input::~Input() {
}
