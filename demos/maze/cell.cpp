#include "cell.h"

Cell::Cell(int x, int y){
	this->gridX = x;
	this->gridY = y;

	// set object and color
	this->loadQuad();
	this->scale = glm::vec3(100, 100, 0);
	this->color.setColor(200, 200, 200);

	std::cout << color.r << std::endl;
}

Cell::~Cell(){
}

void Cell::update(float deltatime){
}


