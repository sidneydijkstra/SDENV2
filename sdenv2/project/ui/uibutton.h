/**
* @file uibutton.h
*
* @brief The UIButton header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UIBUTTON_H
#define UIBUTTON_H

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
* @brief The UIButton class
*/
class UIButton : public UICollection{
public:
	UIButton(Color nomralc, Color hoverc, Color clickc); ///< @brief Constructor of the UIButton
	~UIButton(); ///< @brief Destructor of the UIButton

	virtual void update();

	void setButtonText(std::string message);
	void setButtonScale(float scale);

	bool OnClick();

	Color normal;
	Color hover;
	Color click;

private:
	UIElement* _button;
	UIText* _text;
};

#endif /* end UIBUTTON_H */