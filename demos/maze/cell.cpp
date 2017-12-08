#include "cell.h"

Cell::Cell(int x, int y, float size){
	this->gridX = x;
	this->gridY = y;

	this->disable();
	this->visited = false;

	this->parent = NULL;

	// set object and color
	this->mesh()->loadQuad();
	this->scale = glm::vec3(size/2 - 2, size/2 - 2, 0);

	int _x = size / 2;
	int _y = size / 2;

	_x += x * size;
	_y += y * size;

	this->position = glm::vec3(_x, _y, 0);

	// create left wall
	wallLeft = new Wall();
	wallLeft->scale = glm::vec3(2,size/2,0);
	wallLeft->position = glm::vec3(-(size/2),0,0);
	wallLeft->mesh()->loadQuad();
	this->addChild(wallLeft);

	// create right wall
	wallRight = new Wall();
	wallRight->scale = glm::vec3(2, size / 2, 0);
	wallRight->position = glm::vec3((size / 2), 0, 0);
	wallRight->mesh()->loadQuad();
	this->addChild(wallRight);

	// create top wall
	wallTop = new Wall();
	wallTop->scale = glm::vec3(size / 2, 2, 0);
	wallTop->position = glm::vec3(0, (size / 2), 0);
	wallTop->mesh()->loadQuad();
	this->addChild(wallTop);

	// create top wall
	wallBottom = new Wall();
	wallBottom->scale = glm::vec3(size / 2, 2, 0);
	wallBottom->position = glm::vec3(0, -(size / 2), 0);
	wallBottom->mesh()->loadQuad();
	this->addChild(wallBottom);
}

Cell::~Cell(){
}

void Cell::update(float deltatime){
}

void Cell::closeWall(Cell* c){
	int mx = this->gridX;
	int my = this->gridY;

	int hx = c->gridX;
	int hy = c->gridY;

	if (hx == mx - 1) { // left
		this->wallLeft->active = false;
		c->wallRight->active = false;
	}
	if (hx == mx + 1) { // right
		this->wallRight->active = false;
		c->wallLeft->active = false;
	}
	if (hy == my - 1) { // bottom
		this->wallBottom->active = false;
		c->wallTop->active = false;
	}
	if (hy == my + 1) { // top
		this->wallTop->active = false;
		c->wallBottom->active = false;
	}

}


