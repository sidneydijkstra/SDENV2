
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	void render3DCube(Mesh* mesh, Shader* shader, Scene* scene);

	// renderer function to render a partical system
	void renderParticals(ParticalSystem* particalsystem, Shader* shader, Scene* scene);

	// scene manager
	SceneManager* scenemanager;
private:
	// the window
	GLFWwindow* _window;
	// window size
	int _windowWidth = 1000, _windowHeight = 800;
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

	// shaders
	Shader* normalShader;
	Shader* framebufferShader;
	Shader* shadowDebugShader;

};

#endif /* end renderer */