#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include <networkhandler.h>
#include <package.h>
#include <action.h>

#include "player.h"
#include "map.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:

	Map* _map;

};

#endif /* end MYSCENE_H */
