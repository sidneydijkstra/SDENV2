#include "cell.h"

Cell::Cell(int x, int y, float size){
	this->gridX = x;
	this->gridY = y;

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
	wallLeft->color = Color(100, 0, 255);
	wallLeft->scale = glm::vec3(2,size/2,0);
	wallLeft->position = glm::vec3(-(size/2),0,0);
	wallLeft->mesh()->loadQuad();
	this->addChild(wallLeft);

	// create right wall
	wallRight = new Wall();
	wallRight->color = Color(100, 0, 255);
	wallRight->scale = glm::vec3(2, size / 2, 0);
	wallRight->position = glm::vec3((size / 2), 0, 0);
	wallRight->mesh()->loadQuad();
	this->addChild(wallRight);

	// create top wall
	wallTop = new Wall();
	wallTop->color = Color(100, 0, 255);
	wallTop->scale = glm::vec3(size / 2, 2, 0);
	wallTop->position = glm::vec3(0, (size / 2), 0);
	wallTop->mesh()->loadQuad();
	this->addChild(wallTop);

	// create top wall
	wallBottom = new Wall();
	wallBottom->color = Color(100, 0, 255);
	wallBottom->scale = glm::vec3(size / 2, 2, 0);
	wallBottom->position = glm::vec3(0, -(size / 2), 0);
	wallBottom->mesh()->loadQuad();
	this->addChild(wallBottom);
}

Cell::~Cell(){
}

void Cell::update(float deltatime){
}


