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
#include "hudcanvas.h"
#include "endcanvas.h"
#include "menucanvas.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

	Level* _level;
	HudCanvas* _hudCanvas;
	EndCanvas* _endCanvas;
	MenuCanvas* _menuCanvas;

	FrameBuffer* fbTop;
	FrameBuffer* fbBottom;

	int _levelType;

	void loadLevelA();
	void loadLevelB();
	void loadLevelC();

	bool pause;
private:
};

#endif /* end MYSCENE_H */
