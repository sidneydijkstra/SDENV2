
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

	bool visited;

	void disable() { color = Color(100,100,100); };
	void enable() { color = Color(255, 255, 255); };
	void inside() { color = Color(0, 150, 0); };
	void path() { color = Color(200, 0, 0); };

	void closeWall(Cell* c);

	Cell* parent;

	Wall* wallLeft;
	Wall* wallRight;
	Wall* wallTop;
	Wall* wallBottom;
private:
};

#endif /* end CELL_H */
