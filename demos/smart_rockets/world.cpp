#include "world.h"

World::World(){
	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);

	rocket = new Rocket();

	this->addChild(rocket);

}

World::~World()
{
}

void World::update(float deltatime)
{
	rocket->update(deltatime);

	if (this->getInput()->getKeyDown(GLFW_KEY_SPACE)) {
		rocket->reload();
	}
}
