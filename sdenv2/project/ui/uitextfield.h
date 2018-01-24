/**
* @file uitextfield.h
*
* @brief The UITextField header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UITEXTFIELD_H
#define UITEXTFIELD_H

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
* @brief The UITextField class
*/
class UITextField : public UICollection {
public:
	UITextField(std::string message, const char* font = ""); ///< @brief Constructor of the UIButton
	~UITextField(); ///< @brief Destructor of the UIButton

	virtual void update();

	UIText* text();

private:
	UIText* _text;
};

#endif /* end UITEXTFIELD_H */