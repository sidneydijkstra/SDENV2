#include "uitoggle.h"

UIToggle::UIToggle(bool value){
	this->size = glm::vec3(20, 20, 0);
	this->_isOn = !value;
	this->_offset = 4;

	_main = new UIElement();
	_main->size = this->size;
	_main->color = Color(30,30,30);
	this->add(_main);

	_inner = new UIElement();
	_inner->size = this->size - this->_offset;
	this->add(_inner);

	this->_switch();
}

UIToggle::~UIToggle(){
	delete _main;
	delete _inner;
}

void UIToggle::update(){
	if (_main->size != this->size) {
		_main->size = this->size;
	}
	if (_inner->size != this->size - this->_offset) {
		_inner->size = this->size - this->_offset;
	}

	if (_main->OnClick()) {
		this->_switch();
	}
}

bool UIToggle::isOn(){
	return this->_isOn;
}

void UIToggle::_switch(){
	this->_isOn = !this->_isOn;

	if (this->_isOn) {
		_inner->color = Color(0, 255, 0);
	}else {
		_inner->color = Color(255, 0, 0);
	}
}
