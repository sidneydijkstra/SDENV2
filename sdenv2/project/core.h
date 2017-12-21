
/**
* @file core.h
*
* @brief The Core header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef CORE_H
#define CORE_H


#include <iostream>
#include <map>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include freetype
#include <ft2build.h>
#include FT_FREETYPE_H  

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
#include "scenemanager.h"
#include "sdenv2config.h"

/**
* @brief The Core class
*/
class Core
{
public:
	Core(); ///< @brief Constructor of the Core
	~Core(); ///< @brief Destructor of the Core

	/// @brief the main run function of the Core
	/// @return void
	bool run();

	SceneManager* scenemanager; ///< @brief the scenemanager pointer
private:
	GLFWwindow* _window; ///< @brief the window pointer

	Renderer* renderer; ///< @brief the renderer pointer

	/// @brief create the window
	/// @return void
	void createWindow();
	/// @brief initialize the Core
	/// @return void
	void init();

	/// @brief calculate the deltatime
	/// @return void
	void calculateDeltatime();
	GLfloat _deltaTime = 0.0f; ///< @brief the deltatime
	GLfloat _lastFrame = 0.0f; ///< @brief the lastframe time
	/// @brief calculate the fps
	/// @return void
	void calculateFPS();
	GLfloat _currentTime; ///< @brief the currenTime
	GLfloat _lastTime; ///< @brief the lastTime
	GLfloat _fps; ///< @brief the fps
	Text* _textfps;  ///< @brief the fps text

	// shaders
	Shader* normal3DShader;  ///< @brief the normal 3D shader
	Shader* normal2DShader;  ///< @brief the normal 2D shader
	Shader* framebufferShader; ///< @brief the framebuffer shader
	Shader* textShader; ///< @brief the text shader

	// TEMP DEBUG VAR
	bool renderTriangle = true; ///< @brief the renderTriangle
};

#endif /* end CORE_H */