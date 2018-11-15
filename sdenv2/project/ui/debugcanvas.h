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

#include "input.h"
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

	// function vor renderer and core to set
	void setFps(std::string str);

	// vars for renderer and core to use
	bool lineRender;

private:
	UIButton* _button;
	UITextField* _fps;
	UIToggle* _toggle;
	UITextField* _mousepos;
};

#endif /* end DEBUGCANVAS_H */