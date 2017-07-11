
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
#include "camera.h";

class Renderer
{
public:
	Renderer();
	~Renderer();

	// main loop function
	void run();

	// renderer functions to render objects
	void render3DCube(Mesh* mesh, Shader* shader, Scene* scene);
private:
	// the window
	GLFWwindow* _window;
	// window size
	int _windowWidth = 1000, _windowHeight = 800;
	// create the window
	void createWindow();

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

	// scene manager
	SceneManager* scenemanager;
};

#endif /* end renderer */