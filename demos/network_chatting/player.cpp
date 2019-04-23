#include "player.h"

Player::Player() {
	this->mesh()->loadQuad();
	this->position = glm::vec3(SWIDTH/2, SHEIGHT/2, 0);
	this->scale = glm::vec3(15, 15, 1);

	this->color = Color(255, 0 ,0);

	_moveSpeed = 64;
	networkID = 0;
}

Player::~Player() {

}

void Player::update(float deltatime) {
	if (Input::getInstance()->getKey(GLFW_KEY_W)) {
		this->position.y += _moveSpeed * deltatime;
	}

	if (Input::getInstance()->getKey(GLFW_KEY_S)) {
		this->position.y -= _moveSpeed * deltatime;
	}

	if (Input::getInstance()->getKey(GLFW_KEY_A)) {
		this->position.x -= _moveSpeed * deltatime;
	}

	if (Input::getInstance()->getKey(GLFW_KEY_D)) {
		this->position.x += _moveSpeed * deltatime;
	}
}