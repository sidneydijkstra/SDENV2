#include "collision.h"


Collision::Collision(){
	_isStatic = false;
}	

void Collision::update(float deltatime) {

}

void Collision::collide(Collision * _col){
	if (!this->isColliding(_col))
		return;

	if (_col->_isStatic) {
		this->position = this->getBoarderPlacementPoint(_col);
	}
		
}

bool Collision::isColliding(Collision * _col){
	// Collision x-axis?
	bool x = _col->position.x + _col->size.x * 2 >= this->position.x && this->position.x + this->size.x*2 >= _col->position.x;
	bool y = _col->position.y + _col->size.y * 2 >= this->position.y && this->position.y + this->size.y * 2 >= _col->position.y;
	return x && y;
}

glm::vec3 Collision::getPointToBoarder(Collision * _col){
	glm::vec3 point = glm::vec3();
	if(this->position.x >= _col->position.x)
		point.x = glm::max(_col->position.x, this->position.x - this->size.x);
	else
		point.x = glm::min(_col->position.x, this->position.x + this->size.x);


	if (this->position.y >= _col->position.y)
		point.y = glm::max(_col->position.y, this->position.y - this->size.y);
	else
		point.y = glm::min(_col->position.y, this->position.y + this->size.y);

	return point;
}

glm::vec3 Collision::getBoarderPlacementPoint(Collision * _col) {
	glm::vec3 point = this->position;

	if (!this->collision(_col))
		return point;


	glm::vec3 collisionPointA = this->getPointToBoarder(_col);
	glm::vec3 collisionPointB = _col->getPointToBoarder(this);

	if (_col->leftCollision(this)) {
		point.x = this->position.x - (collisionPointA.x - collisionPointB.x);
		std::cout << "left --- ";
	}
	else if (_col->rightCollision(this)) {
		point.x = this->position.x + (collisionPointB.x - collisionPointA.x);
		std::cout << "rigth --- ";
	}

	if (_col->bottomCollision(this)) {
		point.y = this->position.y - (collisionPointA.y - collisionPointB.y);
		std::cout << "bottom" << std::endl;
	}
	else if (_col->topCollision(this)) {
		point.y = this->position.y + (collisionPointB.y - collisionPointA.y);
		std::cout << "top" << std::endl;
	}

	return point;
}


bool Collision::collision(Collision * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->size;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->size;

	if (tPos.x + tSize.x > ePos.x - eSize.x && tPos.x - tSize.x < ePos.x + eSize.x && tPos.y + tSize.y > ePos.y - eSize.y && tPos.y - tSize.y < ePos.y + eSize.y) {
		return true;
	}

	return false;
}

bool Collision::topCollision(Collision * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->size;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->size;

	float a = ePos.y - eSize.y;
	float b = tPos.y + (tSize.y);

	float c = ePos.y + eSize.y;
	float d = tPos.y + tSize.y;

	if (this->collision(e) && a < b && c > d) {
		return true;
	}
	return false;
}

bool Collision::bottomCollision(Collision * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->size;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->size;

	float a = ePos.y + eSize.y;
	float b = tPos.y - (tSize.y);

	float c = ePos.y - eSize.y;
	float d = tPos.y - tSize.y;

	if (this->collision(e) && a > b && c < d) {
		return true;
	}
	return false;
}

bool Collision::leftCollision(Collision * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->size;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->size;

	float a = ePos.x + eSize.x;
	float b = tPos.x - (tSize.x);

	float c = ePos.x - eSize.x;
	float d = tPos.x - tSize.x;



	if (this->collision(e) && a > b && c < d) {
		return true;
	}

	return false;
}

bool Collision::rightCollision(Collision * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->size;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->size;

	float a = ePos.x - eSize.x;
	float b = tPos.x + (tSize.x);

	float c = ePos.x + eSize.x;
	float d = tPos.x + tSize.x;

	if (this->collision(e) && a < b && c > d) {
		return true;
	}

	return false;
}

Collision::~Collision(){
}

