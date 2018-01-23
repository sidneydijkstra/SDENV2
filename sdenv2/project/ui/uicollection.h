/**
* @file uielement.h
*
* @brief The UICollection header file.
*
* This file is part of SDENV2, a 2D/3D OpenGL framework.
* This file belongs to the SDENUI part of the framework.
*/

#ifndef UICOLLECTION_H
#define UICOLLECTION_H

#include <iostream>

#include "mesh.h"
#include "sprite.h"
#include "ui/uielement.h"
#include "ui/uitext.h"

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/**
* @brief The UICollection class
*/
class UICollection {
public:
	UICollection(); ///< @brief Constructor of the UICollection
	~UICollection(); ///< @brief Destructor of the UICollection

	virtual void update();

	glm::vec3 position;
	glm::vec3 size;

	bool active;

	void addElement(UIElement* element);
	void removeElement(UIElement* element);
	std::vector<UIElement*> getAllElements();
	int getElementsCount();

	void addUIText(UIText* text);
	void removeUITextt(UIText* text);
	std::vector<UIText*> getAllUIText();
	int getUITextCount();

	glm::vec3 center();
	glm::vec3 left();
	glm::vec3 top();

private:
	std::vector<UIElement*> _elements;
	std::vector<UIText*> _texts;
};

#endif /* end UICOLLECTION_H */