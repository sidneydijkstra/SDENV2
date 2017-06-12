
#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// include mesh
#include "mesh.h"
// include shader
#include "shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	// main loop function
	void run();

	// renderer functions to render objects
	void render3DCube(Mesh* mesh, Shader* shader);
private:
	// the window
	GLFWwindow* _window;
	// window size
	int _windowWidth = 1000, _windowHeight = 800;
	// create the window
	void createWindow();

	// shaders
	Shader* normalShader;
};

#endif /* end renderer */