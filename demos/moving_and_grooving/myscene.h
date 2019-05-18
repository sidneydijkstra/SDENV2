#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include <scene.h>
#include <mesh.h>

#include "collision.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:
	std::vector<Entity*> points;

	Collision* player;
	Collision* cube;
};

#endif /* end MYSCENE_H */
