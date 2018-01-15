#include "world.h"

World::World(){
	/*
	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);
	*/

	for (int i = 0; i < 3; i++){
		rockets.push_back(new Rocket());
	}
	rockets[1]->position = glm::vec3(0,250,0);
	rockets[2]->position = glm::vec3(300, 500,0);

	this->addChild(rockets[0]);
	this->addChild(rockets[1]);
	this->addChild(rockets[2]);

}

World::~World()
{
}

void World::update(float deltatime){
	rockets[0]->position = glm::vec3(input()->getMouseX(),input()->getMouseY(),0);

	rockets[0]->update(deltatime);
	rockets[1]->update(deltatime);
	rockets[2]->update(deltatime);
}
