#include "splashscreen.h"

SplashScreen::SplashScreen(){

	this->addSpriteAnimator();
	
	std::vector<const char*> anim = {
		"assets/intro_1.png",
		"assets/intro_2.png",
	};
	this->spriteAnimator()->addAnimations(anim, 0.8f, 0, 0);
	this->spriteAnimator()->setAnimation(0);

}

SplashScreen::~SplashScreen()
{
}

void SplashScreen::update(float deltatime)
{
	this->spriteAnimator()->update();
}
