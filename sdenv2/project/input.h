/**
* @file input.h
*
* @brief The Input header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The Input class
*/
class Input
{
public:
	/// @brief get the Instance of the Input
	/// @return Mesh*
	static Input* getInstance();
	~Input(); ///< @brief Destructor of the Input

	/// @brief initialize the Input
	/// @param the window Input usage
	/// @return void
	static void init(GLFWwindow * window);

	/// @brief update the Input
	/// @return void
	static void update();

	/// @brief get the mouse x position
	/// @return float
	static float getMouseX();
	/// @brief get the mouse y position
	/// @return float
	static float getMouseY();

	/// @brief get if key is pressed
	/// @param the key
	/// @return bool
	static bool getKey(int _keycode);
	/// @brief get if key is down
	/// @param the key
	/// @return bool
	static bool getKeyDown(int _keycode);

	/// @brief get if mouse button is pressed
	/// @param the mouse button
	/// @return bool
	static bool getMouseButton(int _mousebuttoncode);
	/// @brief get if mouse button is down
	/// @param the mouse button
	/// @return bool
	static bool getMouseButtonDown(int _mousebuttoncode);

	/// @brief the key callback function
	/// @return void
	static void _handleKey(GLFWwindow* window, int key, int scancode, int action, int mode);
	/// @brief the mouse callback function
	/// @return void
	static void _handleMouseButton(GLFWwindow* window, int button, int action, int mode);
	/// @brief the mouse callback function
	/// @return void
	static void _handleMouse(GLFWwindow* window, double xpos, double ypos);
	/// @brief the scroll wheel callback function
	/// @return void
	static void _handleScroll(GLFWwindow* window, double xoffset, double yoffset);

	/// @brief delete the Input
	/// @return void
	static void delInput() { delete instance; };

private:
	Input(); ///< @brief Constructor of the Input
	static Input* instance; ///< @brief the main instance of the Input
	GLFWwindow* window; ///< @brief the window the Input usage

	bool _keys[GLFW_KEY_LAST]; ///< @brief the keys
	bool _keysDown[GLFW_KEY_LAST]; ///< @brief the keys down

	bool _mouse[GLFW_MOUSE_BUTTON_LAST]; ///< @brief the keys
	bool _mouseDown[GLFW_MOUSE_BUTTON_LAST]; ///< @brief the keys down

	float _mouseX; ///< @brief the mouse x
	float _mouseY; ///< @brief the mouse y
}; 

#endif /* end input */