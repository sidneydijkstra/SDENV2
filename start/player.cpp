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
	if (this->input()->getKey(GLFW_KEY_A)) {
		this->vel.x = -1;
	}else if(this->input()->getKey(GLFW_KEY_D)){
		this->vel.x = 1;
	}else {
		this->vel.x = 0;
	}

	this->position += vel * 60.0f * deltatime;
}
 