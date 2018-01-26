#include "scenemanager.h"

// scene manager constructor
SceneManager::SceneManager(){
	_currentScene = NULL;

	// sceneManager create message
	std::cout << "created new sceneManager" << std::endl;
}

// sceneManager update 
void SceneManager::update(float deltatime){
	// check scene for state
	if (this->getCurrentScene()->state == this->getCurrentScene()->pref) {
		this->prefScene();
	}
	else if (this->getCurrentScene()->state == this->getCurrentScene()->next) {
		this->nextScene();
	}
	else if (this->getCurrentScene()->state == this->getCurrentScene()->go) {
		this->setActiveScene(this->getCurrentScene()->gotoScene);
	}

	// update current scene
	getCurrentScene()->update(deltatime);

	/// this is a debug option for moving the camera
	//getCurrentScene()->camera()->move(deltatime);
}

void SceneManager::addCurrentScene(Scene * _scene){
	_scene->state = _scene->none;

	_listScene.push_back(_scene);

	if (_scene->getSceneMode() == SCENE2D) {
		glDisable(GL_DEPTH_TEST); // <-- for 2D
		return;
	}

	if (_scene->getSceneMode() == SCENE3D) {
		glEnable(GL_DEPTH_TEST); // <-- for 3D
		return;
	}
}

void SceneManager::setCurrentScene(Scene * _scene){
	if (_currentScene != NULL) {
		_currentScene->state = _scene->none;
	}

	_currentSceneIndex = _listScene.size();
	this->addCurrentScene(_scene);

	_currentScene = _scene;
	_currentScene->state = _currentScene->show;

	if(_scene->getSceneMode() == SCENE2D){
		glDisable(GL_DEPTH_TEST); // <-- for 2D
		return;
	}

	if (_scene->getSceneMode() == SCENE3D) {
		glEnable(GL_DEPTH_TEST); // <-- for 3D
		return;
	}
}

void SceneManager::setActiveScene(int index){
	if (index < 0 && index > _listScene.size() - 1) {
		return;
	}
	this->setCurrentScene(_listScene[index]);
}

void SceneManager::nextScene(){
	_listScene[_currentSceneIndex]->state = _listScene[_currentSceneIndex]->none;

	_currentSceneIndex++;
	if (_currentSceneIndex > _listScene.size() - 1) {
		_currentSceneIndex = 0;
	}

	_listScene[_currentSceneIndex]->state = _listScene[_currentSceneIndex]->show;
}

void SceneManager::prefScene(){
	_listScene[_currentSceneIndex]->state = _listScene[_currentSceneIndex]->none;

	_currentSceneIndex--;
	if (_currentSceneIndex < 0) {
		_currentSceneIndex = _listScene.size() - 1;
	}

	_listScene[_currentSceneIndex]->state = _listScene[_currentSceneIndex]->show;
}

// scene manager deconstructor
SceneManager::~SceneManager(){
}


