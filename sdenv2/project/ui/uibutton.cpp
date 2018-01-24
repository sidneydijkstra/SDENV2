#include "uibutton.h"

UIButton::UIButton(Color nomralc, Color hoverc, Color clickc){
	this->size = glm::vec3(100, 30, 0);
	this->position = glm::vec3(SWIDTH / 2, SHEIGHT / 2, 0);

	_button = new UIElement();
	_text = new UIText("", 0.5);

	this->addElement(_button);
	this->addUIText(_text);

	_button->size = glm::vec3(this->size.x, this->size.y, 0);
	_button->position = this->center();

	_button->color = nomralc;
	this->normal = nomralc;
	this->hover = hoverc;
	this->click = clickc;

	_text->position = this->center();
	_text->message = "button";
	_text->color = glm::vec3(0,0,0);
}

UIButton::~UIButton(){
	delete _button;
	delete _text;
}

void UIButton::update(){
	if (_button->size != this->size) {
		_button->size = glm::vec3(this->size.x, this->size.y, 0);
	}

	if (_button->OnHovor()) {
		_button->color = this->hover;
	}
	else {
		_button->color = this->normal;
	}

	if (_button->OnHold()) {
		_button->color = this->click;
	}
}

void UIButton::setButtonText(std::string message){
	_text->message = message;
}

void UIButton::setButtonScale(float scale){
	_text->scale = scale;
}

bool UIButton::OnClick(){
	return _button->OnClick();
}
