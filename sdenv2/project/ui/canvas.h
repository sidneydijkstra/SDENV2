/**
* @file canvas.h
*
* @brief The Canvas header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef CANVAS_H
#define CANVAS_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "ui/uielement.h"
#include "ui/uicollection.h"
#include "ui/uitext.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The Canvas class
*/
class Canvas {
public:
	Canvas(); ///< @brief Constructor of the Canvas
	~Canvas(); ///< @brief Destructor of the Canvas

	virtual void update();

	bool active;

	void addChild(UICollection* child);
	void removeChild(UICollection* child);
	std::vector<UICollection*> getAllChilderen();
	int getChildCount();

	glm::vec3 center();

private:
	std::vector<UICollection*> _childeren;
};

#endif /* end CANVAS_H */