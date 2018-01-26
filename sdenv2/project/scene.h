/**
* @file scene.h
*
* @brief The Scene header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
*
*/

#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#include <SOIL.h>

#include "light.h"
#include "camera.h"
#include "input.h"
#include "entity.h"
#include "text.h"
#include "color.h"
#include "framebuffer.h"
#include "savemanager.h"
#include "ui.h"

/**
* @brief The Scene class
*/
class Scene
{
public:
	Scene(); ///< @brief Constructor of the Scene
	virtual ~Scene(); ///< @brief Destructor of the Scene

	/// @brief the update function of the Scene
	/// @param the deltatime
	/// @return void
	virtual void update(float deltatime);

	/// @brief get the input
	/// @return Input*
	Input* input() { return _input; };
	/// @brief get the camera of the scene
	/// @return Camera*
	Camera* camera() { return _camera; };

	/// @brief set the mode of the scene SCENE2D or SCENE3D
	/// @param the mode
	/// @return void
	void setSceneMode(int m) { _scenemode = m; };
	/// @brief get the mode of the scene SCENE2D or SCENE3D
	/// @return int
	int getSceneMode() { return _scenemode; };

	/// @brief add a child to the Scene
	/// @param the child
	/// @return void
	void addChild(Entity* entity) { _childeren.push_back(entity); };
	/// @brief remove a child from the Scene
	/// @param the child
	/// @return void
	void removeChild(Entity* entity);
	/// @brief get the child count
	/// @return int
	int getChildCount() { return _childeren.size(); };
	/// @brief get all the childeren
	/// @return std::vector<Entity*>
	std::vector<Entity*> getChilderen() { return _childeren; };

	/// @brief add a canvas to the Scene
	/// @param the canvas
	/// @return void
	void addCanvas(Canvas* canvas) { _canvases.push_back(canvas); };
	/// @brief remove a canvas from the Scene
	/// @param the canvas
	/// @return void
	void removeCanvas(Canvas* text);
	/// @brief get the canvas count
	/// @return int
	int getCanvasCount() { return _canvases.size(); };
	/// @brief get all the canvases
	/// @return std::vector<Canvas*>
	std::vector<Canvas*> getCanvases() { return _canvases; };

	/// @brief add a framebuffer to the Scene
	/// @param the framebuffer
	/// @return void
	void addFramebuffer(FrameBuffer* fb) { _framebuffers.push_back(fb); };
	/// @brief remove a framebuffer from the Scene
	/// @param the framebuffer
	/// @return void
	void removeFramebuffer(FrameBuffer* fb);
	/// @brief get the framebuffer count
	/// @return int
	int getFramebufferCount() { return _framebuffers.size(); };
	/// @brief get all the framebuffer
	/// @return std::vector<FrameBuffer*>
	std::vector<FrameBuffer*> getFramebuffers() { return _framebuffers; };

	/// @brief add a light to the Scene
	/// @param the light
	/// @return void
	void addLight() { _light = new Light(); };
	/// @brief get the light of the Scene
	/// @return Light*
	Light* getLight() { return _light; };


	// hanndle scene switching
	static enum State {
		none, show, pref, next, go
	};
	State state;
	int gotoScene;
	void NEXT() { state = next; };
	void PREF() { state = pref; };
	void GOTO(int index) { state = go; gotoScene = index; };

private:
	Input* _input; ///< @brief the Input
	Camera* _camera; ///< @brief the Camera of the Scene
	Light* _light; ///< @brief the Light of the Scene

	std::vector<Entity*> _childeren; ///< @brief the list of childeren
	std::vector<Canvas*> _canvases; ///< @brief the list of texts
	std::vector<FrameBuffer*> _framebuffers; ///< @brief the list of framebuffers

	int _scenemode; ///< @brief the Mode of the Scene
};

#endif /* end SCENE_H */