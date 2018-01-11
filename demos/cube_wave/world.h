#ifndef WORLD_H
#define WORLD_H


#include <scene.h>

#include "cube.h"

class World : public Scene
{
public:
	World();
	virtual ~World();

	virtual void update(float deltatime);

private:
	std::vector<Cube*> cubes;
	float angle;
};

#endif /* end WORLD_H */
