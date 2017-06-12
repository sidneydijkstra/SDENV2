#include "renderer.h"

// renderer constructor
Renderer::Renderer(){
	// instantiate glfw
	glfwInit();

	// create window
	createWindow();
}


// create the window
void Renderer::createWindow() {
	// create a window object
	_window = glfwCreateWindow(_windowWidth, _windowHeight, "SDEN", nullptr, nullptr);

	// check if window is created
	if (_window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(_window);

	// GLFW Options
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// initializing GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
	}

	// tell openGl the size of the render window
	glfwGetFramebufferSize(_window, &_windowWidth, &_windowHeight);

	// set view port
	glViewport(0, 0, _windowWidth, _windowHeight);

	// set openGL options
	glEnable(GL_DEPTH_TEST);
}

// main game loop
void Renderer::run() {
	// init shaders
	normalShader = new Shader("shaders/normal.vert", "shaders/normal.frag");

	Mesh* mymesh = new Mesh();
	mymesh->loadMeshTexture("assets/maja.jpg");

	// game loop
	while (!glfwWindowShouldClose(_window)) {

		// clear color buffer
		glClearColor(2.1f, 0.7f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		normalShader->use();
		render3DCube(mymesh, normalShader);

		// Swap the screen buffers
		glfwSwapBuffers(_window);

	}

	delete mymesh;

}

void Renderer::render3DCube(Mesh* mesh, Shader* shader) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->_normalTexture);
	
	// get model matrix
	glm::mat4 model;
	model = glm::scale(model, glm::vec3(1, 1, 1));
	model = glm::translate(model, glm::vec3(0.0f,  0.0f, -2.0f));
	model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	// get view
	glm::mat4 view = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	// get projectioins
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.001f, 100.0f);

	// get uniform locations
	GLint uniformModel = glGetUniformLocation(shader->program, "model");
	GLint uniformView = glGetUniformLocation(shader->program, "view");
	GLint uniformProjection = glGetUniformLocation(shader->program, "projection");

	// set mat4 uniforms
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
	
	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

// renderer deconstructor
Renderer::~Renderer() {
	// delete the window
	delete _window;
}