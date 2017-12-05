
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <map>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// include freetype
#include <ft2build.h>
#include FT_FREETYPE_H  

// include config
#include "sdenv2config.h"

// include shader
#include "shader.h"
// include sceneManager
#include "scenemanager.h"
// include scene
#include "scene.h"
// include mesh
#include "mesh.h"
// include scene
#include "camera.h"
// include framebuffer
#include "framebuffer.h"
// include input
#include "input.h"
// include fontoader
#include "fontloader.h"
// include text
#include "text.h"
// include shader
#include "sprite.h"

// debug
#include "particalsystem.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// main loop function
	bool run();

	// renderer functions to render objects
	void render3D(Mesh* mesh, Shader* shader, Scene* scene);

	void render2D(Mesh* mesh, Shader* shader, Scene* scene);

	// renderer function to render a partical system
	void renderParticals(ParticalSystem* particalsystem, Shader* shader, Scene* scene);

	// renderer function to render text
	void renderText(Shader* shader, Text* text);

	// scene manager
	SceneManager* scenemanager;
private:
	// the window
	GLFWwindow* _window;
	// window size
	int _windowWidth, _windowHeight;
	// create the window
	void createWindow();
	// init renderer
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

	// font loader
	FontLoader* fontloader;
};

#endif /* end renderer */