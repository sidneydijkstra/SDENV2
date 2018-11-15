#include "debugcanvas.h"

DebugCanvas::DebugCanvas(){
	_button = new UIButton(Color(96,96,96), Color(64,64,64), Color(32,32,32));
	_button->size = glm::vec3(50,20,0);
	_button->position = glm::vec3(55,SHEIGHT - 50,0);
	this->addChild(_button);

	_fps = new UITextField("fps: 120");
	_fps->position = glm::vec3(5, SHEIGHT - 25, 0);
	this->addChild(_fps);

	_toggle = new UIToggle(false);
	_toggle->position = glm::vec3(25, SHEIGHT - 95, 0);
	this->addChild(_toggle);

	_mousepos = new UITextField("X: 0 Y: 0");
	_mousepos->position = glm::vec3(5, SHEIGHT - 140, 0);
	this->addChild(_mousepos);

	this->lineRender = false;
}

DebugCanvas::~DebugCanvas(){
	delete _button;
	delete _fps;
	delete _toggle;
	delete _mousepos;
}

void DebugCanvas::update(){
	_button->update();
	_toggle->update();
	this->lineRender = _toggle->isOn();
	_mousepos->text()->message = "X: " + std::to_string(Input::getMouseX()) + " Y: " + std::to_string(Input::getMouseY());
}

void DebugCanvas::setFps(std::string str){
	_fps->text()->message = str;
}
