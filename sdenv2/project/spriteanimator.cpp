#include "spriteanimator.h"

SpriteAnimator::SpriteAnimator(){
	_currentAnimation = 0;
	_currentFrame = 0;
	_timer = 0;

	_filter = 0;
	_wrap = 0;
}

SpriteAnimator::~SpriteAnimator(){
	
}

void SpriteAnimator::update(){
	if (_animations.size() > 0 && glfwGetTime() >= _timer) {
		// go to next aniamtion
		_currentFrame++;
		if (_currentFrame >= _animations[_currentAnimation].size()) {
			_currentFrame = 0;
		}

		// set new timer
		_timer = glfwGetTime() + _animations[_currentAnimation][_currentFrame].delay;
	}
}

void SpriteAnimator::addAnimations(std::vector<const char*> locations, float delay, int filter, int wrap){
	std::vector<Animation> _tmpanim;

	_filter = filter;
	_wrap = wrap;

	for (int i = 0; i < locations.size(); i++){
		Animation anim;
		anim.id = locations[i];
		anim.delay = delay;

		_tmpanim.push_back(anim);
	}

	_animations.push_back(_tmpanim);

	_timer = glfwGetTime() + _animations[_currentAnimation][_currentFrame].delay;
}

void SpriteAnimator::setAnimation(int i){
	if (i == _currentAnimation) {
		return;
	}

	if (i < _animations.size() && i >= 0) {

		_timer = 0;

		_currentAnimation = i;
		_currentFrame = i;
	}else {
		std::cout << "SpriteAnimator: can't set new animation 'int out of bounds' l:" << _animations.size() << " ca: " << i <<  std::endl;
	}
}
