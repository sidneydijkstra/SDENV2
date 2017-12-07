#include "maze.h"

Cell* c;

Maze::Maze(){
	this->setSceneMode(SCENE3D);
	c = new Cell(2,2);
	this->addChild(c);
}	

Maze::~Maze(){
}

void Maze::update(float deltatime) {
	c->update(deltatime);
}
