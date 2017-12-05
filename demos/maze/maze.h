#pragma once

#ifndef MAZE_H
#define MAZE_H

#include <scene.h>
#include <mesh.h>
#include <sdenv2config.h>
#include "cell.h"

class Maze: public Scene
{
public:
	Maze();
	virtual ~Maze();

	virtual void update(float deltatime);

private:
};

#endif /* end MAZE_H */