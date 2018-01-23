#include "uibutton.h"

UIButton::UIButton(Color nomral, Color hover, Color click){
	this->size = glm::vec3(100, 30, 0);
	this->position = glm::vec3(SWIDTH / 2, SHEIGHT / 2, 0);

	_button = new UIElement();
	_text = new UIText("", 0.5);

	this->addElement(_button);
	this->addUIText(_text);

	_button->size = glm::vec3(this->size.x, this->size.y, 0);
	_button->position = this->center();

	_button->color = normal;
	this->normal = normal;
	this->hover = hover;
	this->click = click;

	_text->position = this->center();
	_text->message = "button";
}

UIButton::~UIButton(){
	delete _button;
	delete _text;
}

void UIButton::update(){
	if (_button->OnHovor()) {
		_button->color = this->hover;
	}
	else {
		_button->color = this->hover;
	}

	if (_button->OnClick()) {
		_button->color = this->click;
	}
}

void UIButton::setButtonText(std::string message){
	_text->message = message;
}

void UIButton::setButtonScale(float scale){
	_text->scale = scale;
}
