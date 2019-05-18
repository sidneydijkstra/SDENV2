#include "world.h"

World::World(){
	/*
	int i = 0;
	std::cout << "Enter seed: ";
	std::cin >> i;
	std::srand(i);
	*/

	this->setSceneMode(SCENE3D); // <-- set scene mode

	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 11; y++)
		{
			Cube* c = new Cube();
			this->addChild(c);

			c->position = glm::vec3(x,0,y);
			c->scale = glm::vec3(1,1,1);
			c->color = Color(100,20 * x,20 * y);

			cubes.push_back(c);
		}
	}

	angle = 0;
}

World::~World()
{
	for (int i = 0; i < cubes.size(); i++)
	{
		delete cubes[i];

	}
}


void World::update(float deltatime){
	this->camera()->move(deltatime);

	float offset = 0;
	for (int i = 0; i < cubes.size(); i++)
	{
		offset = glm::distance(cubes[i]->position, glm::vec3(5, 0, 5));
		cubes[i]->scale.y = (sin(angle + (offset)) * 5);
	}
	angle += 0.01f;
}
