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
	this->scale = glm::vec3(25,30,0);

	this->addSpriteAnimator();

	std::vector<const char*> walkanim = {
		"assets/animations/charackters/enemy_walk_1.png",
		"assets/animations/charackters/enemy_walk_2.png",
		"assets/animations/charackters/enemy_walk_3.png",
		"assets/animations/charackters/enemy_walk_4.png"
	};

	this->spriteAnimator()->addAnimations(walkanim, 0.2f, 0, 0);
	this->spriteAnimator()->setAnimation(0);
}

Enemy::~Enemy(){
}

void Enemy::update(float deltatime, std::vector<Tile*> t) {
	this->spriteAnimator()->update();

	// rotate enemy
	//this->rotation.z = atan2(this->position.y - _target->position.y, this->position.x - _target->position.x);
	
	// change direction of enemy
	if (this->position.x < _minx) {
		this->rotation.y = 0;
		_velocity.x = 4;
	}

	if (this->position.x > _maxx) {
		this->rotation.y = 1.570796327f * 2;
		_velocity.x = -4;
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
