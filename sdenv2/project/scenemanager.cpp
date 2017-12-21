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
	getCurrentScene()->camera()->move(deltatime);
}

// scene manager deconstructor
SceneManager::~SceneManager(){
}


