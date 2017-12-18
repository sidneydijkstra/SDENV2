#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H


#include <scene.h>
#include <mesh.h>
#include "player.h"
#include "tile.h"
#include "level.h"
#include "enemy.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

private:
	Player* player;
	Enemy* enemy;


	std::vector<Tile*> tiles;

	Level* _level;
};

#endif /* end MYSCENE_H */
