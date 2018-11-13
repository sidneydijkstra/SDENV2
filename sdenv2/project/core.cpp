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
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // <-- cursor mode

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

	// get projection
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(SWIDTH), 0.0f, static_cast<GLfloat>(SHEIGHT));

	// create ui shader and set projection
	UIShader = new Shader("shaders/ui.vert", "", "shaders/ui.frag");
	UIShader->use();
	UIShader->setMat4("projection", projection);

	// create text shader and set projection
	textShader = new Shader("shaders/text.vert", "", "shaders/text.frag");
	textShader->use();
	textShader->setMat4("projection", projection);

	// init input
	Input::init(_window);

	// init save managers
	SaveManager::init();

	// init scene manager
	scenemanager = new SceneManager();
	
	// init renderer
	renderer = new Renderer();

	// define deltatime and lastframe
	_deltaTime = 0.0f;
	_lastFrame = 0.0f;

	// create fps text
	_fps = 0;
	_textfps = new Text("assets/arial.ttf", 0.25, glm::vec3(1, 1, 0));
	_textfps->position.y = SHEIGHT - 15;

	// set openGL options for rendering text
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_debugCanvas = NULL;
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

			// render all currentscene mesh's on screen or all costum entitys
			if (fBuffers[i]->isRenderEntitysOnly()) {
				std::vector<Entity*> costumEntitys = fBuffers[i]->getRenderEntitys();
				int size = costumEntitys.size();
				for (int i = 0; i < size; i++){
					renderer->render2D(costumEntitys[i], normal2DShader, scene, glm::vec3(0, 0, 0));
				}
			}
			else {
				renderer->renderScene(scene, normal2DShader, normal3DShader);
			}

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
	int canvascount = scene->getCanvasCount();
	std::vector<Canvas*> Canvases = scene->getCanvases();
	for (int i = 0; i < canvascount; i++) {
		renderer->RenderCanvas(Canvases[i], UIShader, textShader);
	}


	// debug

	// render debug canvas
	if (_debugCanvas == NULL) {
		_debugCanvas = new DebugCanvas();
	}

	_debugCanvas->update();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	renderer->RenderCanvas(_debugCanvas, UIShader, textShader);

	// set render style
	if (!_debugCanvas->lineRender) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}else{
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
		if (_debugCanvas != NULL) {
			_debugCanvas->setFps("fps: " + std::to_string(_fps));
		}
		_lastTime = glfwGetTime();
		_fps = 0;
	}
}

Core::~Core() {
	// delete and save save manager
	SaveManager::getInstance()->close();

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
	delete UIShader;

	// delete fps text
	delete _textfps;
}

