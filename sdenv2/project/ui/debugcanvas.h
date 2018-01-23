/**
* @file debugcanvas.h
*
* @brief The DebugCanvas header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef DEBUGCANVAS_H
#define DEBUGCANVAS_H

#include <iostream>

#include "ui.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The DebugCanvas class
*/
class DebugCanvas : public Canvas{
public:
	DebugCanvas(); ///< @brief Constructor of the DebugCanvas
	~DebugCanvas(); ///< @brief Destructor of the DebugCanvas

	virtual void update();

private:
};

#endif /* end DEBUGCANVAS_H */