#include "renderer.h"

// renderer constructor
Renderer::Renderer(){
	// instantiate glfw
	glfwInit();

	// create window
	this->createWindow();

	// init renderer
	this->init();
}


// create the window
void Renderer::createWindow() {
	// create a window object
	_window = glfwCreateWindow(_windowWidth, _windowHeight, "SDENV2", nullptr, nullptr);

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
	//glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// set view port
	glViewport(0, 0, _windowWidth, _windowHeight);

	// set openGL options
	glEnable(GL_DEPTH_TEST);
}


// renderer debug variables
bool renderTriangle = true;

void Renderer::init() {

	// init shaders
	normalShader = new Shader("shaders/normal.vert", "", "shaders/normal.frag");
	framebufferShader = new Shader("shaders/framebuffer.vert", "", "shaders/framebuffer.frag");
	shadowDebugShader = new Shader("shaders/partical.vert", "", "shaders/partical.frag");

	// init window
	Input::init(_window);

	// init scene manager
	scenemanager = new SceneManager(_window);
}


// main game loop
bool Renderer::run() {
	// clear screen and set background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	// update input
	Input::update();

	// calculate deltattime and fps
	calculateDeltatime();
	calculateFPS();

	// update scene manager and scene manager updates current scene
	scenemanager->update(_deltaTime);

	// render all currentscene mesh's on screen
	normalShader->use();
	int childcount = scenemanager->getCurrentScene()->getChildCount();
	std::vector<Mesh*> childeren = scenemanager->getCurrentScene()->getChilderen();
	Scene* scene = scenemanager->getCurrentScene();
	for (int i = 0; i < childcount; i++) {
		render3DCube(childeren[i], normalShader, scene);
	}

	// debug
	// recompile shader
	if (Input::getKeyDown(GLFW_KEY_G)) {
		normalShader = new Shader("shaders/normal.vert", "", "shaders/normal.frag");
		framebufferShader = new Shader("shaders/framebuffer.vert", "", "shaders/framebuffer.frag");
	}

	// set render style
	if (Input::getKeyDown(GLFW_KEY_N)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Input::getKeyDown(GLFW_KEY_M)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	// Swap the screen buffers
	glfwSwapBuffers(_window);

	// return to while
	return !glfwWindowShouldClose(_window);
}


void Renderer::render3DCube(Mesh* mesh, Shader* shader, Scene* scene) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->_normalTexture);
	
	// get model matrix
	glm::mat4 model;
	model = glm::scale(model, mesh->scale);								// scale
	model = glm::translate(model, mesh->position);						// position
	model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
	model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
	model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z

	// get view
	glm::mat4 view = glm::lookAt(scene->getCamera()->position, scene->getCamera()->position + scene->getCamera()->front, scene->getCamera()->up);
	//glm::mat4 view = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	// get projectioins
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.001f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

	// set uniforms
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	// set object color uniform
	shader->setVec3("fragObjectColor", glm::vec3(1,1,1));
	
	// set lighting uniforms
	if(scene->getLight() != NULL){
		shader->setVec3("fragLightColor", scene->getLight()->lightColor);
		shader->setVec3("fragLightPosition", scene->getLight()->position);
		shader->setVec3("fragViewPosition", scene->getCamera()->position);

		shader->setFloat("fragAmbientStrength", scene->getLight()->ambientStrength);
		shader->setFloat("fragSpecularStrength", scene->getLight()->specularStrength);
	}
	
	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
	glBindVertexArray(0);
}

void Renderer::renderParticals(ParticalSystem * particalsystem, Shader * shader, Scene * scene){
	// get all partical mesh's
	std::vector<Mesh*> particals = particalsystem->getAllParticalsMesh();

	
	// draw all the mesh's
	int size = particals.size();
	for (size_t i = 0; i < size; i++){
		// get mesh
		Mesh* mesh = particals[i];

		// bind VAO
		glBindVertexArray(mesh->_VAO);

		// activate textures
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, mesh->_normalTexture);

		// get model matrix
		glm::mat4 model;
		model = glm::scale(model, mesh->scale);								// scale
		model = glm::translate(model, mesh->position);						// position
		model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
		model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
		model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z

																			// get view
		glm::mat4 view = glm::lookAt(scene->getCamera()->position, scene->getCamera()->position + scene->getCamera()->front, scene->getCamera()->up);
		//glm::mat4 view = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

		// get projectioins
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.001f, 100.0f);

		// set uniforms
		shader->setMat4("model", model);
		shader->setMat4("view", view);
		shader->setMat4("projection", projection);

		// draw partical
		glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
		glBindVertexArray(0);
	}

}

// calculate deltatime
void Renderer::calculateDeltatime() {
	GLfloat _currentFrame = glfwGetTime();
	_deltaTime = _currentFrame - _lastFrame;
	_lastFrame = _currentFrame;
}

// calculate fps 
void Renderer::calculateFPS() {
	_currentTime = glfwGetTime();
	_fps++;
	if (_currentTime - _lastTime >= 1) {
		// print fps
		std::cout << "fps: " << _fps << std::endl;

		_lastTime = glfwGetTime();
		_fps = 0;
	}
}

// renderer deconstructor
Renderer::~Renderer() {
	// delete the window
	delete _window;
	// delete shader
	delete normalShader;
	delete framebufferShader;
	delete shadowDebugShader;
	// delete scene manager
	delete scenemanager;

	Input::delInput();
}