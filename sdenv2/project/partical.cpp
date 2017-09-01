#include "partical.h"

// Partical constructor
Partical::Partical(float lifetime){
	_mesh = new Mesh();
	_mesh->loadCube();

	_lifetime = glfwGetTime() + lifetime;

	//this->velocity.y = 12;
	//this->velocity.x = 7;
}

void Partical::update(float deltatime){

	// velocity calculations
	//this->velocity.y -= 7 * deltatime;

	// add velocity to this mesh position
	_mesh->position += this->velocity * deltatime;

	//this->velocity.x -= (this->velocity.x / 2) * deltatime;

	///std::cout << this->velocity.x * deltatime << std::endl;
}

// Partical deconstructor
Partical::~Partical(){
	// delete mesh
	delete _mesh;
}


