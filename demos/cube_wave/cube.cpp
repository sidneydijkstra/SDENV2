#include "cube.h"

Cube::Cube(){
	this->mesh()->loadCube();
	this->scale = glm::vec3(1, 1, 1);
	this->color = Color(255,0,0);
}

Cube::~Cube()
{
}

void Cube::update(float deltatime){

}
