#include "core.h"

Core::Core(){
	// instantiate glfw
	glfwInit();

	// create window
	this->createWindow();

	// init renderer
	this->init();
}

// create the window
void Core::createWindow() {
	// set window width and height
	int _windowHeight = SHEIGHT;
	int _windowWidth = SWIDTH;

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
}

void Core::init() {
	// init shaders
	normal3DShader = new Shader("shaders/normal3D.vert", "", "shaders/normal3D.frag");
	normal2DShader = new Shader("shaders/normal2D.vert", "", "shaders/normal2D.frag");
	framebufferShader = new Shader("shaders/framebuffer.vert", "", "shaders/framebuffer.frag");

	// create text shader and set projection
	textShader = new Shader("shaders/text.vert", "", "shaders/text.frag");
	textShader->use();
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SWIDTH), 0.0f, static_cast<GLfloat>(SHEIGHT));
	textShader->setMat4("projection", projection);

	// init input
	Input::init(_window);

	// init scene manager
	scenemanager = new SceneManager();
	
	// init renderer
	renderer = new Renderer();

	// define deltatime and lastframe
	_deltaTime = 0.0f;
	_lastFrame = 0.0f;

	// create fps text
	_fps = 0;
	_textfps = new Text("assets/arial.ttf", 0.35, glm::vec3(0, 0, 0));
	_textfps->position.y = SHEIGHT - 20;

	// set openGL options for rendering text
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH_TEST); // <-- for 3D
	glDisable(GL_DEPTH_TEST); // <-- for 2D
}

bool Core::run(){
	// update input
	Input::update();

	// calculate deltattime and fps
	calculateFPS();
	calculateDeltatime();

	// update scene manager and scene manager updates current scene
	scenemanager->update(_deltaTime);

	// get current scene
	Scene* scene = scenemanager->getCurrentScene();

	if (scene->getFramebufferCount() > 0) { // render scene with frame buffer

		std::vector<FrameBuffer*> fBuffers = scene->getFramebuffers();
		for (int i = 0; i < fBuffers.size(); i++) {
			// clear screen and set background
			glm::vec3 c = fBuffers[i]->background.getColor();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.x, c.y, c.z, 1);

			// bind frame buffer
			fBuffers[i]->bind();

			// clear screen and set background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.x, c.y, c.z, 1);

			// render all currentscene mesh's on screen
			renderer->renderScene(scene, normal2DShader, normal3DShader);

			// unbind buffer
			fBuffers[i]->unbind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		// clear screen and set background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);

		// render framebuffers
		for (int i = 0; i < fBuffers.size(); i++) {
			renderer->renderFramebuffer(fBuffers[i], framebufferShader);
		}

	}
	else {
		// clear screen and set background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);

		// render all currentscene mesh's on screen
		renderer->renderScene(scene, normal2DShader, normal3DShader);
	}

	// render all text in scene
	textShader->use();
	int textcount = scene->getTextCount();
	std::vector<Text*> texts = scene->getTexts();
	for (int i = 0; i < textcount; i++) {
		renderer->renderText(texts[i], textShader);
	}

	// display fps
	renderer->renderText(_textfps, textShader);

	// debug

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

// calculate deltatime
void Core::calculateDeltatime() {
	GLfloat _currentFrame = glfwGetTime();
	_deltaTime = _currentFrame - _lastFrame;
	_lastFrame = _currentFrame;
}

// calculate fps
void Core::calculateFPS() {
	_currentTime = glfwGetTime();
	_fps++;
	if (_currentTime - _lastTime >= 1) {

		_textfps->message = "FPS: " + std::to_string(_fps) + " DELTATIME: " + std::to_string(_deltaTime);
		_lastTime = glfwGetTime();
		_fps = 0;
	}
}

Core::~Core() {
	// delete the window
	delete _window;

	// delete scene manager, input and renderer
	delete scenemanager;
	delete renderer;
	Input::delInput();

	// delete shader
	delete normal3DShader;
	delete normal2DShader;
	delete framebufferShader;
	delete textShader;

	// delete fps text
	delete _textfps;
}

