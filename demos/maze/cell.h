
#ifndef CELL_H
#define CELL_H

#include <mesh.h>
#include <sdenv2config.h>

class Cell : public Mesh
{
public:
	Cell(int x, int y);
	~Cell();

	void update(float deltatime);

	int gridX, gridY;

private:
};

#endif /* end CELL_H */
