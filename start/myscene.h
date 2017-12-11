#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H


#include <scene.h>
#include <mesh.h>
#include "myentity.h"
#include "player.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

private:
	std::vector<MyEntity*> entitys;
	Player* player;
};

#endif /* end MYSCENE_H */
