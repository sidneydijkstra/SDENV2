
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <SOIL.h>

#include "scene.h"

#include "camera.h"
#include "mesh.h"

class SceneManager
{
public:
	SceneManager(GLFWwindow* _window);
	~SceneManager();

	// scene manager update
	void update(float deltatime);

	// set current scene
	void setCurrentScene(Scene* _scene) { _currentScene = _scene; };
	// get current scene
	Scene* getCurrentScene() { return _currentScene; };
private:
	// temp current scene variable
	Scene* _currentScene;
};

#endif /* end scenemanager */