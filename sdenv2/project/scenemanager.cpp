#include "scenemanager.h"

// TEMP scenes
Scene* newScene;

// scene manager constructor
SceneManager::SceneManager(GLFWwindow* _window){
	// create input and camera
	_input = new Input(_window);
	_camera = new Camera();

	newScene = new Scene(_input, _camera);
	setCurrentScene(newScene);

	// sceneManager create message
	std::cout << "created new sceneManager" << std::endl;
}

// sceneManager update 
void SceneManager::update(float deltatime){
	// update current scene
	getCurrentScene()->update(deltatime);

	/// this is a debug option for moving the camera
	_camera->move(deltatime, _input);
}

// scene manager deconstructor
SceneManager::~SceneManager(){
	delete newScene;

	// delete input
	delete _input;
	// delete camera
	delete _camera;
}


