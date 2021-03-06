#include "coin.h"

Coin::Coin(glm::vec3 _position){
	this->position = _position;

	this->mesh()->loadQuad();

	this->scale = glm::vec3(12,24,0);
	this->sprite()->loadTexture("assets/coin.png", 0, 0);
}

Coin::~Coin(){
}

void Coin::update(float deltatime){
	this->rotation.y += 5 * deltatime;
}
