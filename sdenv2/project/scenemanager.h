/**
* @file scenemanager.h
*
* @brief The SceneManager header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

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

/**
* @brief The SceneManager class
*/
class SceneManager
{
public:
	SceneManager(); ///< @brief Constructor of the SceneManager
	~SceneManager(); ///< @brief Destructor of the SceneManager

	/// @brief the update function of the SceneManager
	/// @param the deltatime
	/// @return void
	void update(float deltatime);

	/// @brief add a scene to the scene list
	/// @param the Scene
	/// @return void
	void addCurrentScene(Scene* _scene);

	/// @brief add a scene to the scene list and set it as current scene
	/// @param the Scene
	/// @return void
	void setCurrentScene(Scene* _scene);
	/// @brief get the current scene
	/// @return Scene*
	Scene* getCurrentScene() { return _listScene[_currentSceneIndex]; };
private:
	Scene* _currentScene; ///< @brief the current Scene
	std::vector<Scene*> _listScene; ///< @brief the list of Scene's
	int _currentSceneIndex; ///< @brief index of current scene

	void nextScene();
	void prefScene();
};

#endif /* end scenemanager */