#include "object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::update(float deltatime){
	this->vel += this->acc;
	if (Input::getInstance()->getKey(GLFW_KEY_D)) {
		this->acc.x = speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_A)) {
		this->acc.x = -speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_S)) {
		this->acc.y = speed;
	}
	if (Input::getInstance()->getKey(GLFW_KEY_W)) {
		this->acc.y = -speed;
	}
}
