#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H


#include <scene.h>
#include <mesh.h>
#include <sdenv2config.h>
#include "myentity.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

private:
	std::vector<MyEntity*> entitys;
};

#endif /* end MYSCENE_H */
