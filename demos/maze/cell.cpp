#include "cell.h"

Cell::Cell(int x, int y){
	this->gridX = x;
	this->gridY = y;

	// set object and color
	this->loadCube();
	this->scale = glm::vec3(1, 1, 1);
	this->color.setColor(200, 200, 200);

	std::cout << color.r << std::endl;

	this->addSpriteAnimator();
	std::vector<const char*> sp;
	sp.push_back("assets/animations/one.png");
	sp.push_back("assets/animations/two.png");
	sp.push_back("assets/animations/three.png");
	sp.push_back("assets/animations/fore.png");
	sp.push_back("assets/matthijs.png");
	this->spriteAnimator()->setAnimations(sp, 0.2f, 0, 0);
}

Cell::~Cell(){
}

void Cell::update(float deltatime){
	this->spriteAnimator()->update();
}


