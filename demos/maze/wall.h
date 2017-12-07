
#ifndef WALL_H
#define WALL_H

#include <mesh.h>
#include <sdenv2config.h>

class Wall : public Mesh
{
public:
	Wall(int x, int y, float size);
	~Wall();

	void update(float deltatime);

	int gridX, gridY;

private:
};

#endif /* end WALL_H */