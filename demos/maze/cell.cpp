#include "cell.h"

Cell::Cell(int x, int y, float size){
	this->gridX = x;
	this->gridY = y;

	// set object and color
	this->loadQuad();
	this->scale = glm::vec3(size/2 - 2, size/2 - 2, 0);

	int _x = size / 2;
	int _y = size / 2;

	_x += x * size;
	_y += y * size;

	this->position = glm::vec3(_x, _y, 0);
}

Cell::~Cell(){
}

void Cell::update(float deltatime){
}


