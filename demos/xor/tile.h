#pragma once

#ifndef TILE_H
#define TILE_H

#include <entity.h>

class Tile : public Entity
{
public:
	Tile(int _x, int _y, int _w, int _h);
	virtual ~Tile();

	void update(float deltatime);
private:
};

#endif /* end TILE_H */
