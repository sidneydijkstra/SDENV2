/**
* @file uiimage.h
*
* @brief The UIImage header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UIIMAGE_H
#define UIIMAGE_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "ui/uielement.h"
#include "ui/uicollection.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The UIImage class
*/
class UIImage : public UICollection {
public:
	UIImage(); ///< @brief Constructor of the UIImage
	~UIImage(); ///< @brief Destructor of the UIImage

	virtual void update();

	void setTetxture(const char* l);
	void setColor(Color c);
private:
	UIElement* _main;
};

#endif /* end UIIMAGE_H */