#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

// include glew
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// include sprite
#include "sprite.h"

struct animation{
	GLuint id;
	float delay;
};

class SpriteAnimator
{
public:
	SpriteAnimator(Sprite* s);
	virtual ~SpriteAnimator();

	// update
	void update();

	// set new animation
	void setAnimations(std::vector<const char*> locations, float delay, int filter, int wrap);

	GLuint getCurrentAnimation() { return _animations[_currentAnimation].id; };
private:
	std::vector<animation> _animations;
	Sprite* _sprite;
	int _currentAnimation;
	float _timer;
};

#endif /* end SPRITEANIMATOR_H */
