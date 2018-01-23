#include "uicollection.h"

UICollection::UICollection(){
	this->position = glm::vec3(0,0,0);
	this->size = glm::vec3(0, 0, 0);

	this->active = true;
}

UICollection::~UICollection(){
}

void UICollection::update(){
}

void UICollection::addElement(UIElement * element){
	_elements.push_back(element);
	element->parentPosition = (&this->position);
}

void UICollection::removeElement(UIElement * element){
	for (int i = 0; i < _elements.size(); i++) {
		if (_elements[i] == element) {
			_elements.erase(_elements.begin() + i);
			break;
		}
	}
}

std::vector<UIElement*> UICollection::getAllElements(){
	return _elements;
}

int UICollection::getElementsCount(){
	return _elements.size();
}

void UICollection::addUIText(UIText * text){
	_texts.push_back(text);
}

void UICollection::removeUITextt(UIText * text){
	for (int i = 0; i < _texts.size(); i++) {
		if (_texts[i] == text) {
			_texts.erase(_texts.begin() + i);
			break;
		}
	}
}

std::vector<UIText*> UICollection::getAllUIText(){
	return _texts;
}

int UICollection::getUITextCount(){
	return _texts.size();
}

glm::vec3 UICollection::center(){
	return glm::vec3(0, 0, 0);
}

glm::vec3 UICollection::left(){
	float x = this->size.x / 2;
	return -glm::vec3(x, 0 ,0);
}

glm::vec3 UICollection::top(){
	float y = this->size.y / 2;
	return glm::vec3(0, y, 0);
}
