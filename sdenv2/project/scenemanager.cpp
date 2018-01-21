#include "scenemanager.h"

// scene manager constructor
SceneManager::SceneManager(){

	// sceneManager create message
	std::cout << "created new sceneManager" << std::endl;
}

// sceneManager update 
void SceneManager::update(float deltatime){
	// update current scene
	getCurrentScene()->update(deltatime);

	/// this is a debug option for moving the camera
	//getCurrentScene()->camera()->move(deltatime);
}

void SceneManager::setCurrentScene(Scene * _scene){
	_currentScene = _scene;
	
	if(_scene->getSceneMode() == SCENE2D){
		glDisable(GL_DEPTH_TEST); // <-- for 2D
		return;
	}

	if (_scene->getSceneMode() == SCENE3D) {
		glEnable(GL_DEPTH_TEST); // <-- for 3D
		return;
	}

}

// scene manager deconstructor
SceneManager::~SceneManager(){
}


