#ifndef WORLD_H
#define WORLD_H


#include <scene.h>

class World : public Scene
{
public:
	World();
	virtual ~World();

	virtual void update(float deltatime);

private:
};

#endif /* end WORLD_H */
