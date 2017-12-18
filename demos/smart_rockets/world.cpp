#include "world.h"

World::World(){
	/*
	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);
	*/

	for (int i = 0; i < 2; i++){
		rockets.push_back(new Rocket());
	}
	rockets[1]->position = glm::vec3(0,250,0);
	this->addChild(rockets[0]);
	rockets[0]->addChild(rockets[1]);

}

World::~World()
{
}

void World::update(float deltatime){
	rockets[0]->update(deltatime);
	rockets[1]->update(deltatime);
}
