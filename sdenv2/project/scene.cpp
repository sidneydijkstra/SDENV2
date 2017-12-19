#include "scene.h"

// scene constructor
Scene::Scene() {
	// set scene input and camera
	_input = Input::getInstance();
	_camera = new Camera();

	// set scene mode
	_scenemode = SCENE2D;

	// scene create message
	std::cout << "created new scene" << std::endl;
}

// scene update
void Scene::update(float deltatime){
}

void Scene::removeChild(Entity * entity){
	for (int i = 0; i < _childeren.size(); i++) {
		if (_childeren[i] == entity) {
			_childeren.erase(_childeren.begin() + i);
			break;
		}
	}
}

void Scene::removeText(Text * text){
	for (int i = 0; i < _texts.size(); i++) {
		if (_texts[i] == text) {
			_texts.erase(_texts.begin() + i);
			break;
		}
	}
}

void Scene::removeFramebuffer(FrameBuffer * fb){
	for (int i = 0; i < _framebuffers.size(); i++) {
		if (_framebuffers[i] == fb) {
			_framebuffers.erase(_framebuffers.begin() + i);
			break;
		}
	}
}

// scene deconstructor
Scene::~Scene(){
	/*
	// remove childeren
	for (int i = 0; i < _childeren.size(); i++){
		delete _childeren[i];
	}
	// remove text
	for (int i = 0; i < _texts.size(); i++) {
		delete _texts[i];
	}
	// remove framebuffer
	for (int i = 0; i < _framebuffers.size(); i++) {
		delete _framebuffers[i];
	}
	*/

	// clear arrays
	_childeren.clear();
	_texts.clear();
	_framebuffers.clear();

	// remove camera
	delete _camera;
}

