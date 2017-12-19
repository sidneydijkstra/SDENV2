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
	this->scale = glm::vec3(10,10,0);
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

	_velocity.y = -1.0f;
	for (int i = 0; i < t.size(); i++){
		if (t[i]->topCollision(this)) {
			_velocity.y = 0;
		}
	}

	// move enemy
	this->position += _velocity * 20.0f * deltatime;
}
