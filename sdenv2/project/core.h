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

class Core
{
public:
	Core();
	~Core();

	bool run();

	// scene manager
	SceneManager* scenemanager;
private:
	// the window
	GLFWwindow* _window;

	// renderer
	Renderer* renderer;

	// create the window
	void createWindow();
	// init core
	void init();

	// renderer deltatime
	void calculateDeltatime();
	GLfloat _deltaTime = 0.0f;
	GLfloat _lastFrame = 0.0f;
	// renderer fps
	void calculateFPS();
	GLfloat _currentTime;
	GLfloat _lastTime;
	GLfloat _fps;
	Text* _textfps;

	// shaders
	Shader* normal3DShader;
	Shader* normal2DShader;
	Shader* framebufferShader;
	Shader* textShader;

	// TEMP DEBUG VAR
	bool renderTriangle = true;
};

#endif /* end CORE_H */