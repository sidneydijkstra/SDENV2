
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
#include "mesh.h"
#include "text.h"

class Scene
{
public:
	Scene();
	virtual ~Scene();

	// scene update function
	virtual void update(float deltatime);

	// scene get input
	Input* getInput() { return input; };
	// scene get camera
	Camera* getCamera() { return camera; };

	// scene childeren functions
	void addChild(Mesh* mesh) { _childeren.push_back(mesh); };
	void removeChild(Mesh* mesh) { for (int i; i < _childeren.size(); i++) { if (_childeren[i] == mesh) { _childeren.erase(_childeren.begin() + i); delete mesh; break; }; }; };
	int getChildCount() { return _childeren.size(); };
	std::vector<Mesh*> getChilderen() { return _childeren; };

	// scene text functions
	void addText(Text* text) { _texts.push_back(text); };
	void removeText(Text* text) { for (int i; i < _texts.size(); i++) { if (_texts[i] == text) { _texts.erase(_texts.begin() + i); delete text; break; }; }; };
	int getTextCount() { return _texts.size(); };
	std::vector<Text*> getTexts() { return _texts; };

	// scene light functions
	void addLight() { light = new Light(); };
	Light* getLight() { return light; };
private:
	// scene input
	Input* input;
	// scene camera
	Camera* camera;
	// scene light
	Light* light = NULL;

	// childeren
	std::vector<Mesh*> _childeren;

	// childeren
	std::vector<Text*> _texts;
};

#endif /* end scene */