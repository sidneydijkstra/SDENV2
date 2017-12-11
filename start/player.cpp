#include "player.h"

Player::Player(){
	this->mesh()->loadQuad();
	this->scale = glm::vec3(10, 60, 0);
	this->position = glm::vec3(SWIDTH/2, SHEIGHT/2, 0);
}

Player::~Player()
{
}

void Player::update(float deltatime){
}
 