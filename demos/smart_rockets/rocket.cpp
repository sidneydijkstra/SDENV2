#include "rocket.h"

Rocket::Rocket(){
	this->mesh()->loadQuad();
	this->scale = glm::vec3(100, 100, 0);
	this->position = glm::vec3(SWIDTH/2, SHEIGHT/2, 0);

	_current = 0;

	for (int i = 0; i < 150; i++){
		float x = rand() % 200;
		x /= 200;
		x -= 0.5f;
		float y = rand() % 200;
		y /= 200;
		y -= 0.5f;
		movement.push_back(glm::vec3(x, y, 0));
	}
	
	this->addSpriteAnimator();
	std::vector<const char*> locations = { "assets/animations/one.png" ,"assets/animations/two.png" ,"assets/animations/three.png" ,"assets/animations/fore.png" };
	this->spriteAnimator()->addAnimations(locations, 0.4f, 0, 0);
}

Rocket::~Rocket()
{
}

void Rocket::update(float deltatime){
	this->spriteAnimator()->update();
	this->rotation.z += 5 * deltatime;
	/*
	if (_current < 150) {
		vel += acc;
		this->position += vel;
		acc *= 0;
		glm::clamp(vel, glm::vec3(-4), glm::vec3(4));
		this->position += movement[_current] * 10.0f;
		_current++;
	}*/
}

void Rocket::addForce(glm::vec3 force){
	acc = force;
}
