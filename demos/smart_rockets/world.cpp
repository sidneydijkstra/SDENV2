#include "world.h"

World::World(){
	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);

	for (int i = 0; i < 50; i++){
		rockets.push_back(new Rocket());
		this->addChild(rockets[i]);
	}
}

World::~World()
{
}

void World::update(float deltatime){
	for (int i = 0; i < 50; i++){
		rockets[i]->update(deltatime);
	}
}
