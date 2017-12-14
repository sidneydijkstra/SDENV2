#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H


#include <scene.h>
#include <mesh.h>
#include "player.h"
#include "tile.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

private:
	Player* player;
	std::vector<Tile*> tiles;
};

#endif /* end MYSCENE_H */
