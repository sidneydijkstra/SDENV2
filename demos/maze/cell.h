
#ifndef CELL_H
#define CELL_H

#include <entity.h>
#include <sdenv2config.h>

#include "wall.h"

class Cell : public Entity{
public:
	Cell(int x, int y, float size);
	~Cell();

	void update(float deltatime);

	int gridX, gridY;

private:
	Wall* wallLeft;
	Wall* wallRight;
	Wall* wallTop;
	Wall* wallBottom;
};

#endif /* end CELL_H */
