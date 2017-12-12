#ifndef WORLD_H
#define WORLD_H


#include <scene.h>

#include "rocket.h"

class World : public Scene
{
public:
	World();
	virtual ~World();

	virtual void update(float deltatime);

private:
	std::vector<Rocket*> rockets;
};

#endif /* end WORLD_H */
