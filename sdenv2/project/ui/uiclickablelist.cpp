#include "uiclickablelist.h"

UIClickableList::UIClickableList(){
	_background = new UIElement();
	_background->color = Color(200,200,200);
	this->addElement(_background);
}

UIClickableList::~UIClickableList(){
	for (int i = 0; i < _items.size(); i++){
		delete _items[i];
	}
	_items.clear();

	delete _background;
}

void UIClickableList::update(){
}

void UIClickableList::addItem(std::string name){
	UIText* t = new UIText("", 0.4, glm::vec3(0.5,0.5,0.5));
	t->center = false;
	t->position = glm::vec3(0, 20 * (_items.size() + 1), 0);
	t->message = name;
	this->addUIText(t);
	_items.push_back(t);

	_background->position = glm::vec3(50, t->position.y / 2 + 17, 0);
	_background->size = glm::vec3(55, t->position.y / 2, 0);
}

std::string UIClickableList::getSelectedItem()
{
	return std::string();
}
