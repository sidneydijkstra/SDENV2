#include "uiimage.h"

UIImage::UIImage(){
	_main = new UIElement();
	_main->position = glm::vec3(0,0,0);
	_main->size = glm::vec3(0,0,0);
	this->addElement(_main);
}

UIImage::~UIImage(){
	delete _main;
}

void UIImage::update()
{
	_main->size = this->size;
}

void UIImage::setTetxture(const char * l){
	_main->sprite()->loadTexture(l, 0, 0);
}

void UIImage::setColor(Color c){
	_main->sprite()->removeTexture();
	_main->color = c;
}
