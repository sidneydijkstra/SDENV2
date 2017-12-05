#include "spriteanimator.h"

SpriteAnimator::SpriteAnimator(Sprite* s){
	_sprite = s;
	_currentAnimation = 0;
	_timer = 0;
}

SpriteAnimator::~SpriteAnimator(){
	
}

void SpriteAnimator::update(){
	if (glfwGetTime() >= _timer) {
		// go to next aniamtion
		_currentAnimation++;
		if (_currentAnimation >= _animations.size()) {
			_currentAnimation = 0;
		}

		// set new timer
		_timer = glfwGetTime() + _animations[_currentAnimation].delay;
	}
}

void SpriteAnimator::setAnimations(std::vector<const char*> locations, float delay, int filter, int wrap){
	_animations.clear();
	_currentAnimation = 0;
	
	for (int i = 0; i < locations.size(); i++){
		animation a;
		_sprite->loadTexture(locations[i], filter, wrap);
		a.id = _sprite->getTexture();
		a.delay = delay;

		_animations.push_back(a);
	}

	_timer = glfwGetTime() + _animations[_currentAnimation].delay;
}
