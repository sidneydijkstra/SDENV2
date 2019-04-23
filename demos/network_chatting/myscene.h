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

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:

	void connected();

	std::vector<Player*> _networkPlayers;
	Player* _player;

	Timer _timer;

	Canvas* _canvas;
	UIButton* _button;
	UITextField* _message;

	// network packages
	Package* p_updatePosition;
};

#endif /* end MYSCENE_H */
