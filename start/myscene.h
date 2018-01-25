#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H


#include <scene.h>
#include <mesh.h>
#include <timer.h>
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
	Level* _level;
	
	FrameBuffer* fbTop;
	FrameBuffer* fbBottom;
};

#endif /* end MYSCENE_H */
