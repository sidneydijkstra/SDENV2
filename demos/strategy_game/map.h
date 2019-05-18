#pragma once

#ifndef MAP_H
#define MAP_H

#include <entity.h>
#include "tile.h"

class Map : public Entity
{
public:
	Map();
	virtual ~Map();

	void update(float deltatime);

	void generateGrid();
private:
	std::vector<std::vector<Tile*>> _grid;
};

#endif /* end MAP_H */
