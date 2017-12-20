#include "enemy.h"

Enemy::Enemy(Player* target, float minx, float maxx){
	_target = target;
	_minx = minx;
	_maxx = maxx;

	// set velocity
	_velocity = glm::vec3(0,0,0);
	_velocity.x = 4;

	// create enemy
	this->mesh()->loadQuad();
	this->color = Color(170,0,0);
	this->scale = glm::vec3(10,30,0);
}

Enemy::~Enemy(){
}

void Enemy::update(float deltatime, std::vector<Tile*> t) {
	// rotate enemy
	//this->rotation.z = atan2(this->position.y - _target->position.y, this->position.x - _target->position.x);
	
	// change direction of enemy
	if (this->position.x < _minx || this->position.x > _maxx) {
		_velocity.x *= -1;
	}

	_velocity.y = -3.0f;
	for (int i = 0; i < t.size(); i++){
		if (t[i]->topCollision(this)) {
			_velocity.y = 0;
		}
	}

	_offset = 2;

	// move enemy
	this->position += _velocity * 20.0f * deltatime;
}

bool Enemy::collision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (tPos.x + tSize.x > ePos.x - eSize.x && tPos.x - tSize.x < ePos.x + eSize.x && tPos.y + tSize.y > ePos.y - eSize.y && tPos.y - tSize.y < ePos.y + eSize.y) {
		return true;
	}

	return false;
}

bool Enemy::topCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y - eSize.y > tPos.y + (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Enemy::bottomCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.y + eSize.y < tPos.y - (tSize.y - _offset)) {
		return true;
	}
	return false;
}

bool Enemy::leftCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x + eSize.x < tPos.x - (tSize.x - 1)) {
		return true;
	}

	return false;
}

bool Enemy::rightCollision(Entity * e) {

	glm::vec3 tPos = this->position;
	glm::vec3 tSize = this->scale;
	glm::vec3 ePos = e->position;
	glm::vec3 eSize = e->scale;

	if (this->collision(e) && ePos.x - eSize.x > tPos.x + (tSize.x - 1)) {
		return true;
	}

	return false;
}