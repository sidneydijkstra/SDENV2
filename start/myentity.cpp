#include "myentity.h"

Entity* m;

MyEntity::MyEntity(){
	this->mesh()->loadQuad();
	this->color.setColor(200, 200, 10);
	this->scale = glm::vec3(100,100,1);

	this->vel = glm::vec3(std::rand() * 0.001, std::rand() * 0.001, 0);
	this->position = glm::vec3(400,400,0);

	// load animator
	this->addSpriteAnimator();
	std::vector<const char*> sp;
	sp.push_back("assets/animations/one.png");
	sp.push_back("assets/animations/two.png");
	sp.push_back("assets/animations/three.png");
	sp.push_back("assets/animations/fore.png");
	this->spriteAnimator()->setAnimations(sp, 0.2f, 0, 0);

	m = new Entity();
	m->scale = glm::vec3(100,100,0);
	m->color = Color(100, 100, 0);
	m->mesh()->loadQuad();
}

MyEntity::~MyEntity(){
}

void MyEntity::update(float deltatime){
	this->spriteAnimator()->update();

	position += vel * 20.0f * deltatime;

	if (position.x >= SWIDTH || position.x <= 0) {
		vel.x *= -1;
	}
	if (position.y >= SHEIGHT || position.y <= 0) {
		vel.y *= -1;
	}
}


