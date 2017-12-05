#include "myentity.h"

MyEntity::MyEntity(){
	this->loadQuad();
	this->color.setColor(200, 200, 10);
	this->scale = glm::vec3(100,100,1);

	this->vel = glm::vec3(std::rand() * 0.001, std::rand() * 0.001, 0);
	this->position = glm::vec3(400,400,0);
}

MyEntity::~MyEntity(){
}

void MyEntity::update(float deltatime){
	position += vel * 20.0f * deltatime;

	if (position.x >= SWIDTH || position.x <= 0) {
		vel.x *= -1;
	}
	if (position.y >= SHEIGHT || position.y <= 0) {
		vel.y *= -1;
	}
}


