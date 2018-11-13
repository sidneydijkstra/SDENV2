#include "hudcanvas.h"

HudCanvas::HudCanvas(){
	_textCoin = new UITextField("Coins: 0", "");
	_textCoin->position = glm::vec3(SWIDTH - 100, SHEIGHT - 20, 0);
	this->addChild(_textCoin);

	_textHealth = new UITextField("Health: 3", "");
	_textHealth->position = glm::vec3(SWIDTH - 100, SHEIGHT - 40, 0);
	this->addChild(_textHealth);

	_textTimer = new UITextField("Health: 3", "");
	_textTimer->position = glm::vec3(SWIDTH/2, SHEIGHT- 20, 0);
	this->addChild(_textTimer);
}

HudCanvas::~HudCanvas(){
	delete _textCoin;
	delete _textHealth;
	delete _textTimer;
}

void HudCanvas::update(float deltatime){
}

void HudCanvas::addCoin(std::string message){
	_textCoin->text()->message = message;
}

void HudCanvas::addHealth(std::string message){
	_textHealth->text()->message = message;
}

void HudCanvas::addTimer(std::string message){
	_textTimer->text()->message = message;
}
