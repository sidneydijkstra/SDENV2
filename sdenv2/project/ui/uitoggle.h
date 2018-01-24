/**
* @file uitoggle.h
*
* @brief The UIToggle header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UITOGGLE_H
#define UITOGGLE_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "ui/uielement.h"
#include "ui/uitext.h"
#include "ui/uicollection.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The UIToggle class
*/
class UIToggle : public UICollection {
public:
	UIToggle(bool value); ///< @brief Constructor of the UIToggle
	~UIToggle(); ///< @brief Destructor of the UIToggle

	virtual void update();

	bool isOn();

private:
	UIElement* _main;
	UIElement* _inner;

	void _switch();

	float _offset;
	bool _isOn;
};

#endif /* end UITOGGLE_H */