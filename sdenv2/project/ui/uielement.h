/**
* @file uielement.h
*
* @brief The UIElement header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UIELEMENT_H
#define UIELEMENT_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "input.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The UIElement class
*/
class UIElement{
public:
	UIElement(); ///< @brief Constructor of the Timer
	~UIElement(); ///< @brief Destructor of the Timer

	bool OnHovor();
	bool OnHold();
	bool OnClick();

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 size;

	Color color;

	bool active;

	Sprite* sprite() { return _sprite; };
	Mesh* mesh() { return _mesh; };
	Input* input() { return _input; };

	glm::vec3 getWorldPosition() { return this->position + (*parentPosition); };
	glm::vec3* parentPosition;

private:
	Mesh* _mesh;
	Sprite* _sprite;

	Input* _input;

	bool _OnHover;
	bool _OnClickDown;
	bool _OnClickUp;
	bool _OnClick;
	//bool _OnEnter;
	//bool _OnExit;
};

#endif /* end UIELEMENT_H */