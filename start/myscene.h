#pragma once

#ifndef MYSCENE_H
#define MYSCENE_H

#include "../sdenv2/project/scene.h"
#include "../sdenv2/project/mesh.h"
#include "myentity.h"

class MyScene: public Scene
{
public:
	MyScene();
	virtual ~MyScene();

	virtual void update(float deltatime);

private:
};

#endif /* end MYSCENE_H */
