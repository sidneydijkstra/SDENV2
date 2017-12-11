#include "rocket.h"

Rocket::Rocket(){
	this->mesh()->loadQuad();
	this->scale = glm::vec3(8, 30, 0);
	this->position = glm::vec3(SWIDTH/2, 0, 0);

	_current = 0;

	for (int i = 0; i < 150; i++){
		movement.push_back(glm::vec3((rand() % 4) - 2, (rand() % 4) - 2, 0));
	}

}

Rocket::~Rocket()
{
}

void Rocket::update(float deltatime){
	if (_current < 150) {
		this->position += movement[_current];
		_current++;
	}
}

void Rocket::reload()
{
	this->position = glm::vec3(SWIDTH / 2, 0, 0);

	_current = 0;

	for (int i = 0; i < 150; i++) {
		movement.push_back(glm::vec3((rand() % 5) - 2, (rand() % 5) - 2, 0));
	}
}
