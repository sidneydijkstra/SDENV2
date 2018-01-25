#include "hudcanvas.h"

HudCanvas::HudCanvas(){
	_textCoin = new UITextField("Coins: 0", "");
	_textCoin->position = glm::vec3(SWIDTH - 100, SHEIGHT - 20, 0);
	this->addChild(_textCoin);

	_textHealth = new UITextField("Health: 3", "");
	_textHealth->position = glm::vec3(SWIDTH - 100, SHEIGHT - 40, 0);
	this->addChild(_textHealth);
}

HudCanvas::~HudCanvas(){
	delete _textCoin;
	delete _textHealth;
}

void HudCanvas::update(float deltatime){
}

void HudCanvas::addCoin(std::string message){
	_textCoin->text()->message = message;
}

void HudCanvas::addHealth(std::string message){
	_textHealth->text()->message = message;
}
