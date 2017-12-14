#include "player.h"

Player::Player(){
	this->mesh()->loadQuad();
	this->scale = glm::vec3(10, 60, 0);
	this->position = glm::vec3(SWIDTH/2, SHEIGHT/2, 0);

	velocity = glm::vec3(0.0f);
	acceleration = glm::vec3(0.0f);
}

Player::~Player()
{
}

void Player::update(float deltatime, Tile* t){
	this->velocity += acceleration * deltatime;
	this->position += velocity * 40.0f * deltatime;

	glm::clamp(this->velocity, glm::vec3(4.0f), glm::vec3(4.0f));

	this->acceleration *= 0;

	if (this->input()->getKey(GLFW_KEY_A)) {
		this->velocity.x = -4;
	}else if(this->input()->getKey(GLFW_KEY_D)){
		this->velocity.x = 4;
	}else {
		this->velocity.x = 0;
	}

	if (t->collision(this)) {
		this->color = Color(255,0,0);
		this->velocity.y = 0;
	}else {
		acceleration.y = -9.9f;
		this->color = Color(0, 0, 0);
	}

	if (input()->getKey(GLFW_KEY_SPACE)) {
		this->velocity.y = 8;
	}
	//this->position += vel * 100.0f * deltatime;
	//this->position = glm::vec3(input()->getMouseX(), input()->getMouseY(), 0);
}
 