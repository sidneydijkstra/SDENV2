#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include <scene.h>
#include <mesh.h>
#include <timer.h>
#include <networkhandler.h>

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);
private:
	Canvas* _canvas;
	UICollection* _collection;
	UIText* _message;
};

#endif /* end MYSCENE_H */
