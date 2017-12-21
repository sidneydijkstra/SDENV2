#include "spriteanimator.h"

SpriteAnimator::SpriteAnimator(){
	_currentAnimation = 0;
	_timer = 0;

	_filter = 0;
	_wrap = 0;
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

	_filter = filter;
	_wrap = wrap;

	for (int i = 0; i < locations.size(); i++){
		Animation anim;
		anim.id = locations[i];
		anim.delay = delay;

		_animations.push_back(anim);
	}

	_timer = glfwGetTime() + _animations[_currentAnimation].delay;
}
