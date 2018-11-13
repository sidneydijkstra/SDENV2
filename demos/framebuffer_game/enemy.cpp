#include "enemy.h"

Enemy::Enemy(Player* target, float minx, float maxx){
	_target = target;
	_minx = minx;
	_maxx = maxx;

	// set collision offset
	this->setOffset(2);

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

	// move enemy
	this->position += _velocity * 20.0f * deltatime;
}