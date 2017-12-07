
#ifndef WALL_H
#define WALL_H

#include <entity.h>
#include <sdenv2config.h>

class Wall : public Entity
{
public:
	Wall();
	~Wall();

	void update(float deltatime);

	int gridX, gridY;

private:
};

#endif /* end WALL_H */