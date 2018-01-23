#include "input.h"

Input* Input::instance = NULL;

// input constructor
Input::Input(){
	// set all key bools to false
	for (int i = 0; i < GLFW_KEY_LAST; i++) {
		_keys[i] = false;
		_keysDown[i] = false;
	}

	// set all button bools to false
	for (int i = 0; i < GLFW_MOUSE_BUTTON_LAST; i++) {
		_mouse[i] = false;
		_mouseDown[i] = false;
	}

	_mouseX = 0;
	_mouseY = 0;
}

Input* Input::getInstance(){
	if (instance == NULL)
	{
		std::cout << "instance of input made!" << std::endl;
		instance = new Input();
	}

	return instance;
}

void Input::init(GLFWwindow * window){
	Input::getInstance()->window = window;

	// Set the required callback functions
	glfwSetKeyCallback(window, _handleKey);
	glfwSetMouseButtonCallback(window, _handleMouseButton);
	glfwSetCursorPosCallback(window, _handleMouse);
	glfwSetScrollCallback(window, _handleScroll);
}

// input update
void Input::update(){
	// pull events
	glfwPollEvents();
}

// get mouse x
float Input::getMouseX() {
	return Input::getInstance()->_mouseX;
}

// get mouse y
float Input::getMouseY() {
	return Input::getInstance()->_mouseY;
}

// get key press
bool Input::getKey(int _keycode) {
	return Input::getInstance()->_keys[_keycode];
}

bool Input::getKeyDown(int _keycode) {
	if (Input::getInstance()->_keys[_keycode] && !Input::getInstance()->_keysDown[_keycode]) {
		Input::getInstance()->_keysDown[_keycode] = true;
		return true;
	}else if (!Input::getInstance()->_keys[_keycode] && Input::getInstance()->_keysDown[_keycode]) {
		Input::getInstance()->_keysDown[_keycode] = false;
	}
	return false;
}

bool Input::getMouseButton(int _mousebuttoncode){	
	return Input::getInstance()->_mouse[_mousebuttoncode];
}

bool Input::getMouseButtonDown(int _mousebuttoncode){
	if (Input::getInstance()->_mouse[_mousebuttoncode] && !Input::getInstance()->_mouseDown[_mousebuttoncode]) {
		Input::getInstance()->_mouseDown[_mousebuttoncode] = true;
		return true;
	}
	else if (!Input::getInstance()->_mouse[_mousebuttoncode] && Input::getInstance()->_mouseDown[_mousebuttoncode]) {
		Input::getInstance()->_mouseDown[_mousebuttoncode] = false;
	}
	return false;
}

// key handeler
void Input::_handleKey(GLFWwindow * window, int key, int scancode, int action, int mode){
	if (key >= 0 && key <= GLFW_KEY_LAST) {
		if (action == GLFW_PRESS) {
			Input::getInstance()->_keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			Input::getInstance()->_keys[key] = false;
		}
	}

	// exit on ESC
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Input::_handleMouseButton(GLFWwindow * window, int button, int action, int mode){
	if (button >= 0 && button <= GLFW_KEY_LAST) {
		if (action == GLFW_PRESS) {
			Input::getInstance()->_mouse[button] = true;
		}
		else if (action == GLFW_RELEASE) {
			Input::getInstance()->_mouse[button] = false;
		}
	}
}


// mouse handeler
void Input::_handleMouse(GLFWwindow * window, double xpos, double ypos){
	Input::getInstance()->_mouseX = (float)xpos;
	Input::getInstance()->_mouseY = ((float)ypos - 800) * -1;
}

// scroll handeler
void Input::_handleScroll(GLFWwindow * window, double xoffset, double yoffset){
	// code here
}

// input deconstructor
Input::~Input() {
}