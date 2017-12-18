#include "enemy.h"

Enemy::Enemy(Player* target){
	_target = target;

	this->mesh()->loadQuad();
	this->color = Color(0,170,0);
	this->position = glm::vec3(SWIDTH/2,SHEIGHT/2,0);
	this->scale = glm::vec3(10,10,0);
}

Enemy::~Enemy(){
}

void Enemy::update(float deltatime){
	this->rotation.z = atan2(this->position.y - _target->position.y, this->position.x - _target->position.x);
	//std::cout << "rotation: " << atan2(this->position.y - _target->position.y, this->position.x - _target->position.x) << std::endl;
}
