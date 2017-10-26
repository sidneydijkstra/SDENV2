#include "scenemanager.h"

// TEMP scenes
Scene* newScene;

// scene manager constructor
SceneManager::SceneManager(GLFWwindow* _window){

	newScene = new Scene();
	setCurrentScene(newScene);

	// sceneManager create message
	std::cout << "created new sceneManager" << std::endl;
}

// sceneManager update 
void SceneManager::update(float deltatime){
	// update current scene
	getCurrentScene()->update(deltatime);

	/// this is a debug option for moving the camera
	getCurrentScene()->getCamera()->move(deltatime);
}

// scene manager deconstructor
SceneManager::~SceneManager(){
	delete newScene;
	// delete camera
}


