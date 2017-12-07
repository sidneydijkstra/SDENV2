#include "maze.h"

Maze::Maze(){
	this->setSceneMode(SCENE2D);

	worldsize = 10;

	// create grid
	for (int y = 0; y < worldsize; y++) {
		std::vector<Cell*> cells;
		for (int x = 0; x < worldsize; x++) {
			cells.push_back(new Cell(x,y, SWIDTH/worldsize));
			this->addChild(cells[x]);
		}
		grid.push_back(cells);
	}

}	

Maze::~Maze(){
}

void Maze::update(float deltatime) {
}
