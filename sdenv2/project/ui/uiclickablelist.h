/**
* @file uiclickablelist.h
*
* @brief The UIClickableList header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UICLICKABLELIST_H
#define UICLICKABLELIST_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "ui/uielement.h"
#include "ui/uitext.h"
#include "ui/uitextfield.h"
#include "ui/uicollection.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The UIClickableList class
*/
class UIClickableList : public UICollection {
public:
	UIClickableList(); ///< @brief Constructor of the UIClickableList
	~UIClickableList(); ///< @brief Destructor of the UIClickableList

	virtual void update();

	void addItem(std::string name);
	std::string getSelectedItem();

private:
	std::vector<UIText*> _items;
	UIElement* _background;
};

#endif /* end UICLICKABLELIST_H */