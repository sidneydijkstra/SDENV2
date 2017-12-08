#pragma once

#ifndef MAZE_H
#define MAZE_H

#include <scene.h>
#include <entity.h>
#include <sdenv2config.h>
#include "cell.h"
#include <stack>

class Maze: public Scene
{
public:
	Maze();
	virtual ~Maze();

	virtual void update(float deltatime);

private:
	bool isSolved;
	bool isDone;

	int worldsize;
	std::vector<std::vector<Cell*>> grid;
	Cell* currentcell;

	void generateMaze();
	void solveMaze();

	std::stack<Cell*> genStack;
	std::vector<Cell*> serStack;
	std::vector<Cell*> path;

	std::vector<Cell*> getNeighbours(Cell* c); 
	std::vector<Cell*> getNeighboursSolve(Cell* c);

};

#endif /* end MAZE_H */
