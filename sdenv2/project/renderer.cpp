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
	// set window width and height
	_windowHeight = SHEIGHT;
	_windowWidth = SWIDTH;

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
Text* txt;
Mesh quad;
FrameBuffer* buffer;

void Renderer::init() {
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
	scenemanager = new SceneManager(_window);

	// init fontloader
	fontloader = new FontLoader();
	_fps = 0;
	_textfps = new Text("assets/arial.ttf", 0.35, glm::vec3(1, 0, 0));
	_textfps->position.y = SHEIGHT - 20;

	// set openGL options for rendering text
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);

	// add frame buffer
	buffer = new FrameBuffer();
	buffer->createFrameBuffer();
	buffer->createNormalTexture(SWIDTH, SHEIGHT);

	// create quad
	quad = Mesh();
	quad.loadQuad();
	quad.scale.y = 0.5f;
}

// main game loop
bool Renderer::run() {

	// ########################## TEMP ##########################

	// update input
	Input::update();

	// calculate deltattime and fps
	calculateDeltatime();
	calculateFPS();

	// update scene manager and scene manager updates current scene
	scenemanager->update(_deltaTime);

	// get current scene
	Scene* scene = scenemanager->getCurrentScene();

	if (scene->getFramebufferCount() > 0) { // render scene with frame buffer
		
		std::vector<FrameBuffer*> fBuffers = scene->getFramebuffers();
		for (int i = 0; i < fBuffers.size(); i++){
			// clear screen and set background
			glm::vec3 c = fBuffers[i]->background.getColor();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.x, c.y, c.z, 1);

			// bind frame buffer
			fBuffers[i]->bind();
			glEnable(GL_DEPTH_TEST);

			// clear screen and set background
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glClearColor(c.x, c.y, c.z, 1);

			// render all currentscene mesh's on screen
			normal2DShader->use();
			int childcount = scene->getChildCount();
			std::vector<Mesh*> childeren = scene->getChilderen();
			for (int i = 0; i < childcount; i++) {
				render2D(childeren[i], normal2DShader, scene);
			}

			// unbind buffer
			fBuffers[i]->unbind();
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}

	// clear screen and set background
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1, 1, 1, 1);

	/*
	// render all currentscene mesh's on screen
	normal2DShader->use();
	int childcount = scene->getChildCount();
	std::vector<Mesh*> childeren = scene->getChilderen();
	for (int i = 0; i < childcount; i++) {
		render2D(childeren[i], normal2DShader, scene);
	}
	*/

	std::vector<FrameBuffer*> fBuffers = scene->getFramebuffers();
	for (int i = 0; i < fBuffers.size(); i++){
		// render framebuffer
		this->renderFramebuffer(fBuffers[i], framebufferShader);
	}
	
	// render all text in scene
	textShader->use();
	int textcount = scene->getTextCount();
	std::vector<Text*> texts = scene->getTexts();
	for (int i = 0; i < textcount; i++) {
		renderText(textShader, texts[i]);
	}
	// display fps
	renderText(textShader, _textfps);


	// debug
	// recompile shader
	if (Input::getKeyDown(GLFW_KEY_G)) {
		normal3DShader = new Shader("shaders/normal3D.vert", "", "shaders/normal3D.frag");
		normal2DShader = new Shader("shaders/normal2D.vert", "", "shaders/normal2D.frag");
		framebufferShader = new Shader("shaders/framebuffer.vert", "", "shaders/framebuffer.frag");
		textShader = new Shader("shaders/text.vert", "", "shaders/text.frag");
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


void Renderer::render3D(Mesh* mesh, Shader* shader, Scene* scene) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	if (mesh->sprite()->getTexture() != NULL) {
		shader->setBool("doTexture", true);

		if (mesh->spriteAnimator() != NULL) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->spriteAnimator()->getCurrentAnimation());
		}else{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->sprite()->getTexture());
		}
		
	}else {
		shader->setBool("doTexture", false);
	}

	// get model matrix
	glm::mat4 model;
	model = glm::translate(model, mesh->position);						// position
	model = glm::scale(model, mesh->scale);								// scale
	model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
	model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
	model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z

	// get view
	glm::mat4 view = glm::lookAt(scene->getCamera()->position, scene->getCamera()->position + scene->getCamera()->front, scene->getCamera()->up); // render 3D

	// get projectioins
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (GLfloat)_windowWidth / (GLfloat)_windowHeight, 0.001f, 100.0f); // render 3D

	// set uniforms
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	shader->setMat4("projection", projection);

	// set object color uniform
	shader->setVec3("fragObjectColor", mesh->color.getColor());
	
	// set lighting uniforms
	if(scene->getLight() != NULL){
		shader->setBool("doLighting", true);

		shader->setVec3("light.color", scene->getLight()->lightColor);
		shader->setVec3("light.position", scene->getLight()->position);
		shader->setVec3("light.viewPosition", scene->getCamera()->position);

		shader->setFloat("light.ambientStrength", scene->getLight()->ambientStrength);
		shader->setFloat("light.specularStrength", scene->getLight()->specularStrength);
	}else {
		shader->setBool("doLighting", false);
	}
	
	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
	glBindVertexArray(0);
}

void Renderer::render2D(Mesh* mesh, Shader* shader, Scene* scene) {
	// bind VAO
	glBindVertexArray(mesh->_VAO);

	// activate textures
	if (mesh->sprite()->getTexture() != NULL) {
		shader->setBool("doTexture", true);

		if (mesh->spriteAnimator() != NULL) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->spriteAnimator()->getCurrentAnimation());
		}else{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, mesh->sprite()->getTexture());
		}
		
	}else {
		shader->setBool("doTexture", false);
	}

	// get model matrix
	glm::mat4 model;
	model = glm::translate(model, mesh->position);						// position
	model = glm::scale(model, mesh->scale);								// scale
	model = glm::rotate(model, mesh->rotation.x, glm::vec3(1, 0, 0));	// rotation x
	model = glm::rotate(model, mesh->rotation.y, glm::vec3(0, 1, 0));	// rotation y
	model = glm::rotate(model, mesh->rotation.z, glm::vec3(0, 0, 1));	// rotation z
	
	glm::mat4 projection = glm::ortho(0.0f, (float)_windowWidth, 0.0f, (float)_windowHeight, 0.0f, 1.0f); // render 2D

	// set uniforms
	shader->setMat4("model", model);
	shader->setMat4("projection", projection);

	// set object color uniform
	shader->setVec3("fragObjectColor", mesh->color.getColor());

	// draw cube
	glDrawArrays(GL_TRIANGLES, 0, mesh->_drawsize);
	glBindVertexArray(0);
}

void Renderer::renderFramebuffer(FrameBuffer * framebuffer, Shader * shader){
	// set shader, frame buffer options and bind texture
	shader->use();
	glBindVertexArray(quad._VAO);
	glBindTexture(GL_TEXTURE_2D, framebuffer->getFrameBufferNormalTexture());

	// get model
	glm::mat4 model;
	model = glm::translate(model, framebuffer->position);
	model = glm::scale(model, framebuffer->size);
	model = glm::rotate(model, framebuffer->rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, framebuffer->rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, framebuffer->rotation.z, glm::vec3(0, 0, 1));

	// get projectioins
	glm::mat4 projection = glm::ortho(0.0f, (float)SWIDTH, 0.0f, (float)SHEIGHT, 0.0f, 1.0f); // render 2D

	// set shader uniforms
	framebuffer->shader()->setMat4("model", model);
	framebuffer->shader()->setMat4("projection", projection);

	// draw framebuffer on quad
	glDrawArrays(GL_TRIANGLES, 0, 6);
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
		model = glm::translate(model, mesh->position);						// position
		model = glm::scale(model, mesh->scale);								// scale
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

void Renderer::renderText(Shader* shader, Text* text){
	// set text color
	shader->setVec3("textColor", text->color);
	
	// set texture and VAO
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(text->_VAO);

	// get message scale and position
	std::string str = text->message;
	float scale = text->scale;
	float x = text->position.x;
	float y = text->position.y;

	// Iterate through all characters
	std::string::const_iterator c;
	int i = 0;
	for (c = str.begin(); c != str.end(); c++){
		// if lerp color set new color
		i++;
		if (text->doColorLerp()) {
			shader->setVec3("textColor", text->getColorLerp(i));
		}

		// get charackter
		Character ch = fontloader->getFont(text->getFont())[*c];

		// set pos
		GLfloat xpos = x + ch.bearing.x * scale;
		GLfloat ypos = y - (ch.size.y - ch.bearing.y) * scale;

		// set width and height
		GLfloat w = ch.size.x * scale;
		GLfloat h = ch.size.y * scale;

		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};

		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);

		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, text->_VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // Be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
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

		_textfps->message = "FPS: " + std::to_string(_fps);
		_lastTime = glfwGetTime();
		_fps = 0;
	}
}

// renderer deconstructor
Renderer::~Renderer() {
	// delete the window
	delete _window;

	// delete shader
	delete normal3DShader;
	delete normal2DShader;
	delete framebufferShader;
	delete textShader;

	// delete scene manager and fontloader
	delete scenemanager;
	delete fontloader;

	// delete input
	Input::delInput();

	// delete fps text
	delete _textfps;

	// TEMP DELETE
	delete buffer;
}